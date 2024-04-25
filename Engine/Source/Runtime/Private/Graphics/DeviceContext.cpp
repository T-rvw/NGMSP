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

	// Update swapchain back buffers.
	uint32 currentBackBufferIndex = m_pSwapChain->GetCurrentBackBufferIndex();
	m_pSwapChain->AcquireNextBackBufferTexture(m_acquireImageSemaphores[currentBackBufferIndex]);
	auto& frameFence = m_pFrameFences[currentBackBufferIndex];
	auto& frameCommandBuffer = m_pCommandBuffers[currentBackBufferIndex];
	frameFence->Wait(1);
	frameFence->Reset(1);

	frameCommandBuffer->Begin();
	m_pSwapChain->BeginRenderPass(frameCommandBuffer);
	m_pSwapChain->EndRenderPass(frameCommandBuffer);
	frameCommandBuffer->End();

	graphicsCommandQueue->Submit(frameCommandBuffer, nullptr, m_acquireImageSemaphores[currentBackBufferIndex], m_renderCompleteSemaphores[currentBackBufferIndex]);
	m_pSwapChain->Present(graphicsCommandQueue, m_renderCompleteSemaphores[currentBackBufferIndex]);
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
	std::vector<IRHIAdapter*> rhiAdapters(adapterCount);
	m_pInstance->EnumerateAdapters(adapterCount, rhiAdapters.data());

	for (const auto* rhiAdapter : rhiAdapters)
	{
		rhiAdapter->GetInfo().Dump();
	}

	// Find a proper GPU to create logical device.
	auto optAdapterIndex = FindBestRHIAdapter(rhiAdapters);
	assert(optAdapterIndex.has_value());
	int32 adapterIndex = optAdapterIndex.value();
	auto& pBestAdapter = rhiAdapters[adapterIndex];
	printf("Select adapter : %s\n", pBestAdapter->GetInfo().Name.c_str());
	pBestAdapter->Init();

	// Query display output info.
	uint32 adapterOutputCount;
	pBestAdapter->EnumerateOutputs(adapterOutputCount, nullptr);
	std::vector<RHIOutputInfo*> outputInfos(adapterOutputCount);
	pBestAdapter->EnumerateOutputs(adapterOutputCount, outputInfos.data());
	for (const auto* outputInfo : outputInfos)
	{
		outputInfo->Dump();
	}

	// Query command queue info to create device.
	printf("\n");
	uint32 commandQueueCICount;
	pBestAdapter->EnumerateCommandQueues(commandQueueCICount, nullptr);
	std::vector<RHICommandQueueCreateInfo*> commandQueueCIs(commandQueueCICount);
	pBestAdapter->EnumerateCommandQueues(commandQueueCICount, commandQueueCIs.data());
	for (const auto& queueCI : commandQueueCIs)
	{
		queueCI->Dump();
	}

	std::vector<RHICommandType> expectQueueTypes{ RHICommandType::Graphics, RHICommandType::Compute, RHICommandType::Copy };
	std::vector<RHICommandQueueCreateInfo*> bestQueueCIs = FindBestCommandQueues(expectQueueTypes, commandQueueCIs);
	for (const auto& bestQueueCI : bestQueueCIs)
	{
		printf("Select %s command queue : %u\n", EnumName(bestQueueCI->Type).data(), bestQueueCI->ID);
	}

	RHIDeviceCreateInfo deviceCI;
	deviceCI.Features = m_features;
	deviceCI.Debug = m_debugMode;
	deviceCI.Validation = m_validationMode;
	deviceCI.CommandQueueCount = static_cast<uint32>(bestQueueCIs.size());
	deviceCI.CommandQueueCreateInfo = bestQueueCIs.data();
	m_pDevice = pBestAdapter->CreateDevice(deviceCI);

	CreateCommandQueues(bestQueueCIs);
}

void DeviceContext::CreateCommandQueues(const std::vector<RHICommandQueueCreateInfo*>& queueCIs)
{
	for (const auto& queueCI : queueCIs)
	{
		auto typeIndex = static_cast<uint32>(queueCI->Type);
		m_pCommandQueues[typeIndex] = m_pDevice->CreateCommandQueue(*queueCI);

		RHICommandPoolCreateInfo commandPoolCI;
		commandPoolCI.Type = queueCI->Type;
		commandPoolCI.QueueID = queueCI->ID;
		m_pCommandPools[typeIndex] = m_pDevice->CreateCommandPool(commandPoolCI);

		RHIFenceCreateInfo fenceCI;
		m_pCommandQueueFences[typeIndex] = m_pDevice->CreateFence(fenceCI);
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

std::optional<int32> DeviceContext::FindBestRHIAdapter(const std::vector<IRHIAdapter*>& adapters)
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

std::optional<int32> DeviceContext::FindBestCommandQueue(RHICommandType commandType, const std::vector<RHICommandQueueCreateInfo*>& createInfos)
{
	std::optional<int32> bestCIIndex;
	float bestScore = -1.0f;
	for (int32 ciIndex = 0, ciCount = static_cast<int32>(createInfos.size()); ciIndex < ciCount; ++ciIndex)
	{
		const auto& createInfo = createInfos[ciIndex];
		if (commandType == createInfo->Type)
		{
			float score = 0.0f;
			if (createInfo->IsDedicated)
			{
				score += 1U << 31;
			}
			score += createInfo->Priority;

			if (score > bestScore)
			{
				bestCIIndex = ciIndex;
				bestScore = score;
			}
		}
	}

	return bestCIIndex;
}

std::vector<RHICommandQueueCreateInfo*> DeviceContext::FindBestCommandQueues(const std::vector<RHICommandType>& commandTypes, const std::vector<RHICommandQueueCreateInfo*>& createInfos)
{
	std::vector<RHICommandQueueCreateInfo*> bestCommandQueueCIs;

	std::unordered_set<int32> queueIndexes;
	for (auto commandType : commandTypes)
	{
		if (auto optIndex = FindBestCommandQueue(commandType, createInfos); optIndex.has_value())
		{
			queueIndexes.insert(optIndex.value());
		}
	}

	for (auto queueIndex : queueIndexes)
	{
		bestCommandQueueCIs.push_back(createInfos[queueIndex]);
	}

	return bestCommandQueueCIs;
}

}