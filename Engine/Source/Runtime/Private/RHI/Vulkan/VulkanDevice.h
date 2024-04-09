#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIDevice.h>

namespace ow
{

class VulkanDevice : public IRHIDevice
{
public:
	VulkanDevice() = default;
	explicit VulkanDevice(VkPhysicalDevice physcialDevice, VkDevice device);
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	virtual ~VulkanDevice();

	virtual void* GetHandle() const override { return m_device; }
	virtual RHICommandQueue CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const override;
	virtual RHIFence CreateFence() const override;
	virtual RHISemaphore CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const override;
	virtual RHISwapChain CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const override;

private:
	VkPhysicalDevice m_physcialDevice = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
};

}