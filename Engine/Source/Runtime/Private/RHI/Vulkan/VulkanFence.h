#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIFence.h>

namespace ow
{

class VulkanFence : public IRHIFence
{
public:
	VulkanFence() = default;
	explicit VulkanFence(VkFence fence);
	VulkanFence(const VulkanFence&) = delete;
	VulkanFence& operator=(const VulkanFence&) = delete;
	VulkanFence(VulkanFence&&) = default;
	VulkanFence& operator=(VulkanFence&&) = default;
	virtual ~VulkanFence();

	virtual void Init() override;

private:
	VkFence m_fence = VK_NULL_HANDLE;
};

}