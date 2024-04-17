#include "D3D12RHIModule.h"

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new D3D12RHIModule();
}

D3D12RHIModule::~D3D12RHIModule()
{
	delete this;
}

IRHIInstance* D3D12RHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	auto& rhiInstance = m_rhiInstances.emplace_back(std::make_unique<D3D12Instance>(createInfo));
	return rhiInstance.get();
}

IRHIDevice* D3D12RHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	auto d3d12Device = static_cast<D3D12Adapter*>(pAdapter)->CreateDevice(createInfo);
	auto& rhiDevice = m_rhiDevices.emplace_back(std::make_unique<D3D12Device>(d3d12Device));
	return rhiDevice.get();
}

IRHICommandQueue* D3D12RHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	auto d3d12CommandQueue = static_cast<D3D12Device*>(pDevice)->CreateCommandQueue(createInfo);
	auto& rhiCommandQueue = m_rhiCommandQueues.emplace_back(std::make_unique<D3D12CommandQueue>(d3d12CommandQueue));
	rhiCommandQueue->SetType(createInfo.Type);
	return rhiCommandQueue.get();
}

IRHISwapChain* D3D12RHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	return nullptr;
}

IRHIFence* D3D12RHIModule::CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo)
{
	return nullptr;
}

IRHISemaphore* D3D12RHIModule::CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo)
{
	return nullptr;
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