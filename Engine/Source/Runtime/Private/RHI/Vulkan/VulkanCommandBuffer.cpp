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
	commandBufferInfo.commandBufferCount = createInfo.BufferCount;
	
	VK_VERIFY(vkAllocateCommandBuffers(pCommandPool->GetDevice()->GetHandle(), &commandBufferInfo, &m_commandBuffer));
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
}

}