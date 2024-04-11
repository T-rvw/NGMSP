#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIDevice.h>

namespace ow
{

class IRHICommandQueue;
class IRHIFence;
class IRHISemaphore;
class IRHISwapChain;

struct RHICommandQueueCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHISwapChainCreateInfo;

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
	virtual IRHICommandQueue* CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const override;
	virtual IRHIFence* CreateFence() const override;
	virtual IRHISemaphore* CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const override;
	virtual IRHISwapChain* CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const override;

private:
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
};

}