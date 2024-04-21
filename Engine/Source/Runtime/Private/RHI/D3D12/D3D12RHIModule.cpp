#include "D3D12RHIModule.h"

#include <RHI/RHITypes.h>

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new D3D12RHIModule();
}

void D3D12RHIModule::Shutdown()
{
	m_rhiTextures.clear();
	m_rhiBuffer.clear();
	m_rhiSemaphores.clear();
	m_rhiFences.clear();
	m_rhiSwapChains.clear();
	m_rhiCommandQueues.clear();

#ifndef NDEBUG
	std::vector<RefCountPtr<ID3D12DebugDevice>> debugDevices;
	for (const auto& device : m_rhiDevices)
	{
		device->ReportLiveObjects();
	}
#endif

	m_rhiDevices.clear();
	m_rhiInstances.clear();

	delete this;
}

IRHIInstance* D3D12RHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	auto& rhiInstance = m_rhiInstances.emplace_back(std::make_unique<D3D12Instance>(createInfo));
	return rhiInstance.get();
}

IRHIDevice* D3D12RHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	auto* pD3D12Adapter = static_cast<D3D12Adapter*>(pAdapter);
	auto d3d12Device = pD3D12Adapter->CreateDevice(createInfo);
	auto& rhiDevice = m_rhiDevices.emplace_back(std::make_unique<D3D12Device>(pD3D12Adapter, d3d12Device));
	return rhiDevice.get();
}

IRHICommandQueue* D3D12RHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	auto* pD3D12Device = static_cast<D3D12Device*>(pDevice);
	auto d3d12CommandQueue = pD3D12Device->CreateCommandQueue(createInfo);
	auto& rhiCommandQueue = m_rhiCommandQueues.emplace_back(std::make_unique<D3D12CommandQueue>(d3d12CommandQueue));
	rhiCommandQueue->SetType(createInfo.Type);
	pD3D12Device->SetCommandQueue(rhiCommandQueue.get());
	return rhiCommandQueue.get();
}

IRHISwapChain* D3D12RHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	auto d3d12SwapChain = static_cast<D3D12Device*>(pDevice)->CreateSwapChain(createInfo);
	auto& rhiSwapChain = m_rhiSwapChains.emplace_back(std::make_unique<D3D12SwapChain>(d3d12SwapChain));
	return rhiSwapChain.get();
}

IRHIFence* D3D12RHIModule::CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo)
{
	auto d3d12Fence = static_cast<D3D12Device*>(pDevice)->CreateFence(createInfo);
	auto& rhiFence = m_rhiFences.emplace_back(std::make_unique<D3D12Fence>(d3d12Fence));
	return rhiFence.get();
}

IRHISemaphore* D3D12RHIModule::CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo)
{
	auto& rhiSemaphore = m_rhiSemaphores.emplace_back(std::make_unique<D3D12Semaphore>(createInfo));
	return rhiSemaphore.get();
}

IRHIBuffer* D3D12RHIModule::CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo)
{
	return nullptr;
}

IRHISampler* D3D12RHIModule::CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo)
{
	return nullptr;
}

IRHITexture* D3D12RHIModule::CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo)
{
	return nullptr;
}

}