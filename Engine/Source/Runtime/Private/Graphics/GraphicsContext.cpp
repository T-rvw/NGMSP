#include <Graphics/GraphicsContext.h>

#include "RHIUtils.h"

#include <Core/Modules/ModuleManager.h>
#include <RHI/RHI.h>

#include <cassert>

namespace ow
{

GraphicsContext::~GraphicsContext()
{
}

void GraphicsContext::Init(const GraphicsCreateInfo& createInfo)
{
	// Load backend specified dll to init graphics.
	ModuleData* pRHILibrary = nullptr;
	switch (createInfo.Backend)
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

	RHIInstanceCreateInfo instanceCI;
	instanceCI.Features = createInfo.Features;
	instanceCI.Debug = RHIDebugMode::Normal;
	instanceCI.Validation = RHIValidationMode::GPU;
	m_pRHIInstance = m_pRHIModule->CreateRHIInstance(instanceCI);
	assert(m_pRHIInstance);

	// Query all RHI adapters.
	uint32 adapterCount;
	m_pRHIInstance->EnumerateAdapters(adapterCount, nullptr);
	std::vector<IRHIAdapter*> rhiAdapters(adapterCount);
	m_pRHIInstance->EnumerateAdapters(adapterCount, rhiAdapters.data());

	// Find a proper GPU to create logical device.
	auto optAdapterIndex = RHIUtils::FindBestRHIAdapter(rhiAdapters);
	assert(optAdapterIndex.has_value());
	int32 adapterIndex = optAdapterIndex.value();
	auto& pBestAdapter = rhiAdapters[adapterIndex];
	printf("Select adapter : %s\n", pBestAdapter->GetInfo().Name.c_str());
	pBestAdapter->Init();

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

	std::vector<RHICommandType> expectQueueTypes { RHICommandType::Graphics, RHICommandType::Compute, RHICommandType::Copy };
	std::vector<RHICommandQueueCreateInfo*> bestQueueCIs = RHIUtils::FindBestCommandQueues(expectQueueTypes, commandQueueCIs);
	for (const auto& bestQueueCI : bestQueueCIs)
	{
		printf("Select %s command queue : %u\n", EnumName(bestQueueCI->Type).data(), bestQueueCI->ID);
	}

	RHIDeviceCreateInfo deviceCI;
	deviceCI.Features = createInfo.Features;
	deviceCI.CommandQueueCount = static_cast<uint32>(bestQueueCIs.size());
	deviceCI.CommandQueueCreateInfo = bestQueueCIs.data();
	m_pRHIDevice = m_pRHIModule->CreateRHIDevice(pBestAdapter, deviceCI);

	// Create command queues and fences.
	for (const auto& bestQueueCI : bestQueueCIs)
	{
		auto typeIndex = static_cast<uint32>(bestQueueCI->Type);
		m_rhiCommandQueues[typeIndex] = m_pRHIModule->CreateRHICommandQueue(m_pRHIDevice, *bestQueueCI);

		RHICommandPoolCreateInfo commandPoolCI;
		commandPoolCI.QueueID = bestQueueCI->ID;
		m_rhiCommandPools[typeIndex] = m_pRHIModule->CreateRHICommandPool(m_pRHIDevice, commandPoolCI);

		RHIFenceCreateInfo fenceCI;
		m_rhiCommandQueueFences[typeIndex] = m_pRHIModule->CreateRHIFence(m_pRHIDevice, fenceCI);
	}
	
	// Create SwapChain to bind to native window.
	RHISwapChainCreateInfo swapChainCI;
	swapChainCI.NativeInstanceHandle = createInfo.NativeInstanceHandle;
	swapChainCI.NativeWindowHandle = createInfo.NativeWindowHandle;
	swapChainCI.BackBufferWidth = createInfo.BackBufferWidth;
	swapChainCI.BackBufferHeight = createInfo.BackBufferHeight;
	swapChainCI.BackBufferCount = 2;
	swapChainCI.Format = RHIFormat::RGBA8_UNORM;
	swapChainCI.ColorSpace = RHIColorSpace::SRGB_NONLINEAR;
	swapChainCI.PresentMode = RHIPresentMode::VSync;
	m_pRHISwapChain = m_pRHIModule->CreateRHISwapChain(m_pRHIDevice, swapChainCI);
}

}