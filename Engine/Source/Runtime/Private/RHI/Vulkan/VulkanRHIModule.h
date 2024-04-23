#pragma once

#include "VulkanAdapter.h"
#include "VulkanBarrier.h"
#include "VulkanBuffer.h"
#include "VulkanCommandBuffer.h"
#include "VulkanCommandPool.h"
#include "VulkanCommandQueue.h"
#include "VulkanDevice.h"
#include "VulkanFence.h"
#include "VulkanInstance.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChain.h"
#include "VulkanTexture.h"

#include <RHI/IRHIModule.h>

namespace ow
{

class VulkanRHIModule : public IRHIModule
{
public:
	virtual RefCountPtr<IRHIInstance> CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIDevice> CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandBuffer> CreateRHICommandBuffer(IRHICommandPool* pCommandPool, const RHICommandBufferCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandPool> CreateRHICommandPool(IRHIDevice* pDevice, const RHICommandPoolCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandQueue> CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISwapChain> CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIFence> CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBarrier> CreateRHIBarrier(IRHIDevice* pDevice, const RHIBarrierCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISemaphore> CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBuffer> CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISampler> CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHITexture> CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) override;
};

}