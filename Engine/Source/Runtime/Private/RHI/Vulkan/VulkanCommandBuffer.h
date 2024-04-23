#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandBuffer.h>

namespace ow
{

class VulkanCommandBuffer : public IRHICommandBuffer
{
public:
	VulkanCommandBuffer() = delete;
	explicit VulkanCommandBuffer(VkCommandBuffer commandBuffer);
	VulkanCommandBuffer(const VulkanCommandBuffer&) = delete;
	VulkanCommandBuffer& operator=(const VulkanCommandBuffer&) = delete;
	VulkanCommandBuffer(VulkanCommandBuffer&&) = default;
	VulkanCommandBuffer& operator=(VulkanCommandBuffer&&) = default;
	virtual ~VulkanCommandBuffer();

	VkCommandBuffer GetHandle() const { return m_commandBuffer; }

private:
	VkCommandBuffer m_commandBuffer = VK_NULL_HANDLE;
};

}