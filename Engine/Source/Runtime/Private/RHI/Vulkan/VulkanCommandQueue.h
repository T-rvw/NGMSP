#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandQueue.h>

namespace ow
{

class VulkanCommandQueue : public IRHICommandQueue
{
public:
	VulkanCommandQueue() = default;
	explicit VulkanCommandQueue(VkQueue queue);
	VulkanCommandQueue(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue& operator=(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue(VulkanCommandQueue&&) = default;
	VulkanCommandQueue& operator=(VulkanCommandQueue&&) = default;
	virtual ~VulkanCommandQueue();

private:
	friend class VulkanRHIModule;

private:
	VkQueue m_queue = VK_NULL_HANDLE;
};

}