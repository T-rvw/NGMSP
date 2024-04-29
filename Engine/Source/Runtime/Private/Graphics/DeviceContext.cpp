#include <Graphics/DeviceContext.h>

#include <unordered_set>

namespace ow
{

DeviceContext::DeviceContext(RHIBackend backend, void* pNativeWindow, uint32 width, uint32 height)
{
	LoadRHIModule(backend);
	CreateRHIInstance();
	CreateLogicalDevice();
	CreateSwapChain(pNativeWindow, width, height);
}

DeviceContext::~DeviceContext()
{
	for (uint32 frameIndex = 0; frameIndex < BackBufferCount; ++frameIndex)
	{
		m_pFrameFences[frameIndex]->Wait(1);
	}
}

void DeviceContext::Update()
{
	auto& graphicsCommandQueue = m_pCommandQueues[static_cast<uint32>(RHICommandType::Graphics)];

	uint32 currentBackBufferIndex = m_pSwapChain->GetCurrentBackBufferIndex();
	m_pSwapChain->AcquireNextBackBufferTexture(m_acquireImageSemaphores[currentBackBufferIndex]);
	auto& frameFence = m_pFrameFences[currentBackBufferIndex];
	auto& frameCommandBuffer = m_pCommandBuffers[currentBackBufferIndex];
	frameFence->Wait(1);
	frameFence->Reset(1);

	frameCommandBuffer->Begin();
	frameCommandBuffer->BeginRenderPass(m_pSwapChain);
	frameCommandBuffer->EndRenderPass();
	frameCommandBuffer->End();

	graphicsCommandQueue->Submit(frameCommandBuffer, nullptr, m_acquireImageSemaphores[currentBackBufferIndex], m_renderCompleteSemaphores[currentBackBufferIndex]);
	m_pSwapChain->Present(m_renderCompleteSemaphores[currentBackBufferIndex]);
	graphicsCommandQueue->Submit(frameFence);

	for (uint32 frameIndex = 0; frameIndex < BackBufferCount; ++frameIndex)
	{
		m_pFrameFences[frameIndex]->Wait(1);
	}
}

void DeviceContext::LoadRHIModule(RHIBackend backend)
{
	ModuleData* pRHILibrary = nullptr;
	switch (backend)
	{
	case RHIBackend::D3D12:
	{
		pRHILibrary = ModuleManager::Get().AddModule("[RHI][D3D12]", "RHID3D12");
		break;
	}
	case RHIBackend::Vulkan:
	{
		pRHILibrary = ModuleManager::Get().AddModule("[RHI][Vulkan]", "RHIVulkan");
		break;
	}
	default:
	{
		assert("Unknown RHI backend.");
		return;
	}
	}

	assert(pRHILibrary);
	m_pRHIModule = static_cast<IRHIModule*>(pRHILibrary->InitFunc());
}

void DeviceContext::CreateRHIInstance()
{
	RHIInstanceCreateInfo instanceCI;
	instanceCI.Features = m_features;
	instanceCI.Debug = m_debugMode;
	instanceCI.Validation = m_validationMode;
	m_pInstance = m_pRHIModule->CreateRHIInstance(instanceCI);
	assert(m_pInstance);
}

void DeviceContext::CreateLogicalDevice()
{
	// Query all RHI adapters.
	uint32 adapterCount;
	m_pInstance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IRHIAdapter*> rhiAdapters(adapterCount);
	m_pInstance->EnumerateAdapters(adapterCount, rhiAdapters.data());

	for (const auto* rhiAdapter : rhiAdapters)
	{
		rhiAdapter->GetInfo().Dump();
	}

	// Find a proper GPU to create logical device.
	auto optAdapterIndex = FindSuitableAdapter(rhiAdapters);
	assert(optAdapterIndex.has_value());
	int32 adapterIndex = optAdapterIndex.value();
	auto& pBestAdapter = rhiAdapters[adapterIndex];
	printf("Select adapter : %s\n", pBestAdapter->GetInfo().Name.c_str());

	// Query display output info.
	uint32 adapterOutputCount;
	pBestAdapter->EnumerateOutputs(adapterOutputCount, nullptr);
	Vector<RHIOutputInfo*> outputInfos(adapterOutputCount);
	pBestAdapter->EnumerateOutputs(adapterOutputCount, outputInfos.data());
	for (const auto* outputInfo : outputInfos)
	{
		outputInfo->Dump();
	}
	
	// Create logical device and required command queues.
	RHIDeviceCreateInfo deviceCI;
	deviceCI.Features = m_features;
	deviceCI.CommandQueueTypes.Enable(RHICommandType::Graphics);
	deviceCI.CommandQueueTypes.Enable(RHICommandType::Compute);
	deviceCI.CommandQueueTypes.Enable(RHICommandType::Copy);
	deviceCI.Debug = m_debugMode;
	deviceCI.Validation = m_validationMode;
	m_pDevice = pBestAdapter->CreateDevice(deviceCI);

	//CreateCommandQueues(bestQueueCIs);
}

void DeviceContext::CreateCommandQueues(const Vector<RHICommandQueueCreateInfo*>& queueCIs)
{
	//for (const auto& queueCI : queueCIs)
	//{
	//	auto typeIndex = static_cast<uint32>(queueCI->Type);
	//	m_pCommandQueues[typeIndex] = m_pDevice->CreateCommandQueue(*queueCI);
	//
	//	RHICommandPoolCreateInfo commandPoolCI;
	//	commandPoolCI.Type = queueCI->Type;
	//	commandPoolCI.QueueID = queueCI->ID;
	//	m_pCommandPools[typeIndex] = m_pDevice->CreateCommandPool(commandPoolCI);
	//
	//	RHIFenceCreateInfo fenceCI;
	//	m_pCommandQueueFences[typeIndex] = m_pDevice->CreateFence(fenceCI);
	//}
}

void DeviceContext::CreateSwapChain(void* pNativeWindow, uint32 width, uint32 height)
{
	RHISwapChainCreateInfo swapChainCI;
	swapChainCI.NativeWindowHandle = pNativeWindow;
	swapChainCI.BackBufferWidth = width;
	swapChainCI.BackBufferHeight = height;
	swapChainCI.BackBufferCount = BackBufferCount;
	swapChainCI.Format = RHIFormat::RGBA8_UNORM;
	swapChainCI.ColorSpace = RHIColorSpace::SRGB_NONLINEAR;
	swapChainCI.PresentMode = RHIPresentMode::VSync;
	m_pSwapChain = m_pDevice->CreateSwapChain(swapChainCI);

	const auto& pGraphicsCommandPool = m_pCommandPools[static_cast<uint32>(RHICommandType::Graphics)];
	for (uint32 frameIndex = 0; frameIndex < BackBufferCount; ++frameIndex)
	{
		RHICommandBufferCreateInfo commandBufferCI;
		m_pCommandBuffers[frameIndex] = pGraphicsCommandPool->CreateCommandBuffer(commandBufferCI);

		RHIFenceCreateInfo fenceCI;
		m_pFrameFences[frameIndex] = m_pDevice->CreateFence(fenceCI);

		RHISemaphoreCreateInfo semaphoreCI;
		m_acquireImageSemaphores[frameIndex] = m_pDevice->CreateSemaphore(semaphoreCI);
		m_renderCompleteSemaphores[frameIndex] = m_pDevice->CreateSemaphore(semaphoreCI);
	}

	// Allocate setup graphics command buffers.
	RHICommandBufferCreateInfo commandBufferCI;
	m_pSetupCommandBuffer = pGraphicsCommandPool->CreateCommandBuffer(commandBufferCI);

	auto& graphicsCommandQueue = m_pCommandQueues[static_cast<uint32>(RHICommandType::Graphics)];

	m_pFrameFences[0]->Reset(1);
	{
		m_pSetupCommandBuffer->Begin();
		m_pSetupCommandBuffer->End();

		graphicsCommandQueue->Submit(m_pSetupCommandBuffer, m_pFrameFences[0]);
	}
	m_pFrameFences[0]->Wait(1);
}

std::optional<int32> DeviceContext::FindSuitableAdapter(const Vector<IRHIAdapter*>& adapters)
{
	std::optional<int32> bestAdapterIndex;
	uint64 bestScore = 0;
	for (int32 adapterIndex = 0, adapterCount = static_cast<int32>(adapters.size()); adapterIndex < adapterCount; ++adapterIndex)
	{
		const IRHIAdapter* pAdapter = adapters[adapterIndex];
		const auto& adapterInfo = pAdapter->GetInfo();

		uint64 score = 0;
		if (GPUAdapterType::Discrete == adapterInfo.Type)
		{
			score += 1ULL << 63;
		}
		else if (GPUAdapterType::Integrated == adapterInfo.Type)
		{
			score += 1ULL << 62;
		}

		score += adapterInfo.VideoMemorySize >> 20;

		if (score > bestScore)
		{
			bestAdapterIndex = adapterIndex;
			bestScore = score;
		}
	}

	return bestAdapterIndex;
}

}