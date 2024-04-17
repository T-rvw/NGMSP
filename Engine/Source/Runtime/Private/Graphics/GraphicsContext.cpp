#include <Graphics/GraphicsContext.h>

#include "RHIUtils.h"

#include <Core/Modules/ModuleManager.h>
#include <RHI/RHI.h>

#include <cassert>

namespace ow
{

GraphicsContext::~GraphicsContext() = default;

void GraphicsContext::InitializeInstance(const RHIInstanceCreateInfo& createInfo)
{
	switch (createInfo.Backend)
	{
	case RHIBackend::D3D12:
	{
		m_pRHILibrary = ModuleManager::Get().LoadModule("[RHI][D3D12]", "RHID3D12");
		break;
	}
	case RHIBackend::Vulkan:
	{
		m_pRHILibrary = ModuleManager::Get().LoadModule("[RHI][Vulkan]", "RHIVulkan");
		break;
	}
	default:
	{
		assert("Unknown RHI backend.");
		break;
	}
	}

	assert(m_pRHILibrary);
	m_pRHIModule = static_cast<IRHIModule*>(m_pRHILibrary->InitFunc());
	m_pRHIInstance = m_pRHIModule->CreateRHIInstance();
	assert(m_pRHIInstance);
	m_pRHIInstance->Init(createInfo);

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

	// Create device and command queues.
	printf("\n");
	uint32 commandQueueCICount;
	pBestAdapter->QueryCommandQueueCreateInfos(commandQueueCICount, nullptr);
	std::vector<RHICommandQueueCreateInfo*> commandQueueCIs;
	pBestAdapter->QueryCommandQueueCreateInfos(commandQueueCICount, commandQueueCIs.data());
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
	deviceCI.Features.Headless = false;
	deviceCI.Features.RayTracing = true;
	deviceCI.Features.MeshShaders = true;
	const RHICommandQueueCreateInfo* const* pData = bestQueueCIs.data();
	auto* pRHIDevice = pBestAdapter->CreateDevice(deviceCI, static_cast<uint32>(bestQueueCIs.size()), bestQueueCIs.data());

	//std::vector<IRHICommandQueue*> commandQueues;
	//std::vector<IRHIFence*> commandQueueFences;
	//for (const auto& bestQueueCI : bestQueueCIs)
	//{
	//	auto rhiCommandQueue = pRHIDevice->CreateCommandQueue(bestQueueCI);
	//	commandQueues.emplace_back(MoveTemp(rhiCommandQueue));
	//	commandQueueFences.push_back(rhiDevice.CreateFence());
	//}
}

}