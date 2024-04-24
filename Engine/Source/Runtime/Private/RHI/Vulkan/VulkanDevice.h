#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIDevice.h>

namespace ow
{

class VulkanAdapter;

class VulkanDevice : public IRHIDevice
{
public:
	VulkanDevice() = delete;
	explicit VulkanDevice(const VulkanAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo);
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	virtual ~VulkanDevice();

	VkDevice GetHandle() const { return m_device; }
	VkPhysicalDevice GetAdapter() const;
	VkInstance GetInstance() const;

	virtual RefCountPtr<IRHISwapChain> CreateSwapChain(const RHISwapChainCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandPool> CreateCommandPool(const RHICommandPoolCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandQueue> CreateCommandQueue(const RHICommandQueueCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBarrier> CreateBarrier(const RHIBarrierCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIFence> CreateFence(const RHIFenceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISemaphore> CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBuffer> CreateBuffer(const RHIBufferCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHITexture> CreateTexture(const RHITextureCreateInfo& createInfo) override;

private:
	const VulkanAdapter* m_pAdapter = nullptr;
	VkDevice m_device = VK_NULL_HANDLE;
};

}