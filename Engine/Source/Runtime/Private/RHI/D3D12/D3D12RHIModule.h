#pragma once

#include "D3D12Adapter.h"
#include "D3D12Buffer.h"
#include "D3D12CommandQueue.h"
#include "D3D12Device.h"
#include "D3D12Fence.h"
#include "D3D12Instance.h"
#include "D3D12Semaphore.h"
#include "D3D12SwapChain.h"
#include "D3D12Texture.h"

#include <RHI/IRHIModule.h>

#include <list>
#include <memory>

namespace ow
{

class D3D12RHIModule : public IRHIModule
{
public:
	virtual RefCountPtr<IRHIInstance> CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIDevice> CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandQueue> CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISwapChain> CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIFence> CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISemaphore> CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBuffer> CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISampler> CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHITexture> CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) override;

private:
	std::list<std::unique_ptr<D3D12Instance>> m_rhiInstances;
};

}