#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIFence.h>

namespace ow
{

class VulkanFence : public IRHIFence
{
public:
	VulkanFence() = default;
	explicit VulkanFence(VkDevice device, VkFence fence);
	VulkanFence(const VulkanFence&) = delete;
	VulkanFence& operator=(const VulkanFence&) = delete;
	VulkanFence(VulkanFence&&) = default;
	VulkanFence& operator=(VulkanFence&&) = default;
	virtual ~VulkanFence();

	virtual void Wait(uint64 timeout) override;
	virtual void Reset() override;

private:
	VkDevice m_device = VK_NULL_HANDLE;
	VkFence m_fence = VK_NULL_HANDLE;
};

}