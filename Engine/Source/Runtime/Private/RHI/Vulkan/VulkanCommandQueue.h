#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandQueue.h>

namespace ow
{

class VulkanDevice;

class VulkanCommandQueue : public IRHICommandQueue
{
public:
	VulkanCommandQueue() = default;
	explicit VulkanCommandQueue(const VulkanDevice* pDevice, const RHICommandQueueCreateInfo& createInfo);
	VulkanCommandQueue(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue& operator=(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue(VulkanCommandQueue&&) = default;
	VulkanCommandQueue& operator=(VulkanCommandQueue&&) = default;
	virtual ~VulkanCommandQueue() = default;

private:
	VkQueue m_queue = VK_NULL_HANDLE;
};

}