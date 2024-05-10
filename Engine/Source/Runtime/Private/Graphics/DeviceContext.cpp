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
		m_frameFences[frameIndex]->Wait(1);
	}
}

void DeviceContext::Update()
{
	auto& graphicsCommandQueue = m_commandQueues[static_cast<uint32>(RHICommandType::Graphics)];

	uint32 currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
	m_swapChain->AcquireNextTexture(m_acquireImageSemaphores[currentBackBufferIndex]);
	auto& frameFence = m_frameFences[currentBackBufferIndex];
	auto& frameCommandBuffer = m_commandBuffers[currentBackBufferIndex];
	frameFence->Wait(1);
	frameFence->Reset(1);

	frameCommandBuffer->Begin();
	frameCommandBuffer->BeginRenderPass(m_swapChain);
	frameCommandBuffer->EndRenderPass();
	frameCommandBuffer->End();

	graphicsCommandQueue->Submit(frameCommandBuffer, nullptr, m_acquireImageSemaphores[currentBackBufferIndex], m_renderCompleteSemaphores[currentBackBufferIndex]);
	m_swapChain->Present(m_renderCompleteSemaphores[currentBackBufferIndex]);
	graphicsCommandQueue->Submit(frameFence);

	for (uint32 frameIndex = 0; frameIndex < BackBufferCount; ++frameIndex)
	{
		m_frameFences[frameIndex]->Wait(1);
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
		Assert("Unknown RHI backend.");
		return;
	}
	}

	Assert(pRHILibrary);
	m_rhiModule = static_cast<IRHIModule*>(pRHILibrary->InitFunc());
}

void DeviceContext::CreateRHIInstance()
{
	RHIInstanceCreateInfo instanceCI;
	instanceCI.Features = m_features;
	instanceCI.Debug = m_debugMode;
	instanceCI.Validation = m_validationMode;
	m_instance = m_rhiModule->CreateRHIInstance(instanceCI);
	Assert(m_instance);
}

void DeviceContext::CreateLogicalDevice()
{
	// Query all RHI adapters.
	uint32 adapterCount;
	m_instance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IRHIAdapter*> rhiAdapters(adapterCount);
	m_instance->EnumerateAdapters(adapterCount, rhiAdapters.data());

	for (const auto* rhiAdapter : rhiAdapters)
	{
		rhiAdapter->GetInfo().Dump();
	}

	// Find a proper GPU to create logical device.
	auto optAdapterIndex = FindSuitableAdapter(rhiAdapters);
	Assert(optAdapterIndex.has_value());
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
	m_device = pBestAdapter->CreateDevice(deviceCI);

	// Get command queue from logical device and create command pools and queue fences.
	for (uint32 typeIndex = 0; typeIndex < RHICommandTypeCount; ++typeIndex)
	{
		auto commandType = static_cast<RHICommandType>(typeIndex);
		if (!deviceCI.CommandQueueTypes.IsEnabled(commandType))
		{
			continue;
		}

		m_commandQueues[typeIndex] = m_device->GetCommandQueue(commandType);

		RHICommandPoolCreateInfo commandPoolCI;
		commandPoolCI.Type = commandType;
		m_commandPools[typeIndex] = m_device->CreateCommandPool(commandPoolCI);
		
		RHIFenceCreateInfo fenceCI;
		m_commandQueueFences[typeIndex] = m_device->CreateFence(fenceCI);
	}
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
	m_swapChain = m_device->CreateSwapChain(swapChainCI);

	const auto& pGraphicsCommandPool = m_commandPools[static_cast<uint32>(RHICommandType::Graphics)];
	for (uint32 frameIndex = 0; frameIndex < BackBufferCount; ++frameIndex)
	{
		RHICommandListCreateInfo commandBufferCI;
		m_commandBuffers[frameIndex] = pGraphicsCommandPool->CreateCommandList(commandBufferCI);

		RHIFenceCreateInfo fenceCI;
		m_frameFences[frameIndex] = m_device->CreateFence(fenceCI);

		RHISemaphoreCreateInfo semaphoreCI;
		m_acquireImageSemaphores[frameIndex] = m_device->CreateSemaphore(semaphoreCI);
		m_renderCompleteSemaphores[frameIndex] = m_device->CreateSemaphore(semaphoreCI);
	}

	// Allocate setup graphics command buffers.
	RHICommandListCreateInfo commandBufferCI;
	m_setupCommandBuffer = pGraphicsCommandPool->CreateCommandList(commandBufferCI);

	auto& graphicsCommandQueue = m_commandQueues[static_cast<uint32>(RHICommandType::Graphics)];

	m_frameFences[0]->Reset(1);
	{
		m_setupCommandBuffer->Begin();
		m_setupCommandBuffer->End();

		graphicsCommandQueue->Submit(m_setupCommandBuffer, m_frameFences[0]);
	}
	m_frameFences[0]->Wait(1);
}

Optional<int32> DeviceContext::FindSuitableAdapter(const Vector<IRHIAdapter*>& adapters)
{
	Optional<int32> bestAdapterIndex;
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