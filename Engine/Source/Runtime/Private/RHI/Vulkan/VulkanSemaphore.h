#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHISemaphore.h>

namespace ow
{

class VulkanDevice;

class VulkanSemaphore : public IRHISemaphore
{
public:
	VulkanSemaphore() = delete;
	explicit VulkanSemaphore(const VulkanDevice* pDevice, const RHISemaphoreCreateInfo& createInfo);
	VulkanSemaphore(const VulkanSemaphore&) = delete;
	VulkanSemaphore& operator=(const VulkanSemaphore&) = delete;
	VulkanSemaphore(VulkanSemaphore&&) = default;
	VulkanSemaphore& operator=(VulkanSemaphore&&) = default;
	virtual ~VulkanSemaphore();

	VkSemaphore GetHandle() const { return m_semaphore; }
	const VkSemaphore* GetAddressOf() const { return &m_semaphore; }

private:
	const VulkanDevice* m_pDevice = nullptr;
	VkSemaphore m_semaphore = VK_NULL_HANDLE;
};

}