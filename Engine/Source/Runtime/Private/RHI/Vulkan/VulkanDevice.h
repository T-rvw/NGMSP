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

class VulkanAdapter;

class VulkanDevice : public IRHIDevice
{
public:
	VulkanDevice() = default;
	explicit VulkanDevice(const VulkanAdapter* pAdapter, VkDevice device);
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	virtual ~VulkanDevice();

	VkDevice GetHandle() const { return m_device; }
	VkPhysicalDevice GetAdapter() const;
	VkInstance GetInstance() const;

private:
	friend class VulkanRHIModule;
	VkQueue CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const;
	VkSemaphore CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const;

private:
	const VulkanAdapter* m_pAdapter = nullptr;
	VkDevice m_device = VK_NULL_HANDLE;
};

}