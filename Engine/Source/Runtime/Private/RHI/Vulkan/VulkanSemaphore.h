#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHISemaphore.h>

namespace ow
{

class VulkanSemaphore : public IRHISemaphore
{
public:
	VulkanSemaphore() = default;
	explicit VulkanSemaphore(VkSemaphore semaphore);
	VulkanSemaphore(const VulkanSemaphore&) = delete;
	VulkanSemaphore& operator=(const VulkanSemaphore&) = delete;
	VulkanSemaphore(VulkanSemaphore&&) = default;
	VulkanSemaphore& operator=(VulkanSemaphore&&) = default;
	virtual ~VulkanSemaphore();

	virtual void Init() override;

private:
	VkSemaphore m_semaphore = VK_NULL_HANDLE;
};

}