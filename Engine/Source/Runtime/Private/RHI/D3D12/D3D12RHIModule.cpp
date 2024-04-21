#include "D3D12RHIModule.h"

#include <RHI/RHITypes.h>

namespace ow
{

C_ABI RHI_API IModule* InitializeModule()
{
	return new D3D12RHIModule();
}

RefCountPtr<IRHIInstance> D3D12RHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Instance>(createInfo);
}

RefCountPtr<IRHIDevice> D3D12RHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	auto* pD3D12Adapter = static_cast<D3D12Adapter*>(pAdapter);
	auto d3d12Device = pD3D12Adapter->CreateDevice(createInfo);
	return MakeRefCountPtr<D3D12Device>(pD3D12Adapter, d3d12Device);
}

RefCountPtr<IRHICommandQueue> D3D12RHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	auto* pD3D12Device = static_cast<D3D12Device*>(pDevice);
	auto d3d12CommandQueue = pD3D12Device->CreateCommandQueue(createInfo);
	auto rhiCommandQueue = MakeRefCountPtr<D3D12CommandQueue>(d3d12CommandQueue);
	rhiCommandQueue->SetType(createInfo.Type);
	pD3D12Device->SetCommandQueue(rhiCommandQueue.Get());
	return rhiCommandQueue;
}

RefCountPtr<IRHISwapChain> D3D12RHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	auto d3d12SwapChain = static_cast<D3D12Device*>(pDevice)->CreateSwapChain(createInfo);
	return MakeRefCountPtr<D3D12SwapChain>(d3d12SwapChain);
}

RefCountPtr<IRHIFence> D3D12RHIModule::CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo)
{
	auto d3d12Fence = static_cast<D3D12Device*>(pDevice)->CreateFence(createInfo);
	return MakeRefCountPtr<D3D12Fence>(d3d12Fence);
}

RefCountPtr<IRHISemaphore> D3D12RHIModule::CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Semaphore>(createInfo);
}

RefCountPtr<IRHIBuffer> D3D12RHIModule::CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Buffer>();
}

RefCountPtr<IRHISampler> D3D12RHIModule::CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo)
{
	return nullptr;
}

RefCountPtr<IRHITexture> D3D12RHIModule::CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Texture>();
}

}