#include "D3D12RHIModule.h"

#include "D3D12Device.h"
#include "D3D12Instance.h"

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new D3D12RHIModule();
}

IRHIInstance* D3D12RHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	return new D3D12Instance(createInfo);
}

IRHIDevice* D3D12RHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	return nullptr;// new D3D12Device(createInfo);
}

IRHISwapChain* D3D12RHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	return nullptr;
}

IRHICommandQueue* D3D12RHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
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