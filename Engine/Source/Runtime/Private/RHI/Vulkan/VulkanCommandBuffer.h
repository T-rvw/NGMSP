#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandBuffer.h>

namespace ow
{

class VulkanCommandPool;

class VulkanCommandBuffer : public IRHICommandBuffer
{
public:
	VulkanCommandBuffer() = delete;
	explicit VulkanCommandBuffer(const VulkanCommandPool* pCommandPool, const RHICommandBufferCreateInfo& createInfo);
	VulkanCommandBuffer(const VulkanCommandBuffer&) = delete;
	VulkanCommandBuffer& operator=(const VulkanCommandBuffer&) = delete;
	VulkanCommandBuffer(VulkanCommandBuffer&&) = default;
	VulkanCommandBuffer& operator=(VulkanCommandBuffer&&) = default;
	virtual ~VulkanCommandBuffer();

	virtual void Begin() override;
	virtual void End() override;

	VkCommandBuffer GetHandle() const { return m_commandBuffer; }
	const VkCommandBuffer* GetAddressOf() const { return &m_commandBuffer; }

private:
	VkCommandBuffer m_commandBuffer = VK_NULL_HANDLE;
};

}