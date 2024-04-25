#include "VulkanCommandBuffer.h"

#include "VulkanCommandPool.h"
#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanCommandPool* pCommandPool, const RHICommandBufferCreateInfo& createInfo)
{
	VkCommandBufferAllocateInfo commandBufferInfo {};
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferInfo.commandPool = pCommandPool->GetHandle();
	commandBufferInfo.commandBufferCount = 1;
	VK_VERIFY(vkAllocateCommandBuffers(pCommandPool->GetDevice()->GetHandle(), &commandBufferInfo, &m_commandBuffer));
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
}

void VulkanCommandBuffer::Begin()
{
	VkCommandBufferBeginInfo beginInfo {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	VK_VERIFY(vkBeginCommandBuffer(m_commandBuffer, &beginInfo));
}

void VulkanCommandBuffer::End()
{
	VK_VERIFY(vkEndCommandBuffer(m_commandBuffer));
}

}