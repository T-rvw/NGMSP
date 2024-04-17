#pragma once

#include "VulkanHeader.h"

#ifdef VK_USE_PLATFORM_WIN32_KHR
#undef CreateSemaphore
#endif

#include <RHI//IRHIDevice.h>

namespace ow
{

struct RHICommandQueueCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHISwapChainCreateInfo;

class VulkanDevice : public IRHIDevice
{
public:
	VulkanDevice() = default;
	explicit VulkanDevice(VkDevice device);
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	virtual ~VulkanDevice();

private:
	VkQueue CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const;
	VkFence CreateFence() const;
	VkSemaphore CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const;
	VkSwapchainKHR CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const;

private:
	friend class VulkanRHIModule;
	VkDevice m_device = VK_NULL_HANDLE;
};

}