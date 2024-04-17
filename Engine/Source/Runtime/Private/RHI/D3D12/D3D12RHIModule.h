#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class D3D12RHIModule : public IRHIModule
{
public:
	virtual ~D3D12RHIModule() = default;

	virtual IRHIInstance* CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
	virtual IRHIDevice* CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) override;

	virtual IRHISwapChain* CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) override;
	virtual IRHICommandQueue* CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) override;

	virtual IRHIFence* CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) override;
	virtual IRHISemaphore* CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) override;

	virtual IRHIBuffer* CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) override;
	virtual IRHISampler* CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) override;
	virtual IRHITexture* CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) override;
};

}