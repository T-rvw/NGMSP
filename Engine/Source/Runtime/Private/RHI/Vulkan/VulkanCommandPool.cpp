#include "VulkanCommandPool.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandPool::VulkanCommandPool(const VulkanDevice* pDevice, const RHICommandPoolCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkCommandPoolCreateInfo commandPoolCI {};
	commandPoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCI.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	commandPoolCI.queueFamilyIndex = createInfo.QueueID;
	VK_VERIFY(vkCreateCommandPool(pDevice->GetHandle(), &commandPoolCI, nullptr, &m_commandPool));
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(m_pDevice->GetHandle(), m_commandPool, nullptr);
}

VkCommandBuffer VulkanCommandPool::CreateCommandBuffer(const RHICommandBufferCreateInfo& createInfo)
{
	VkCommandBufferAllocateInfo commandBufferInfo {};
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferInfo.commandPool = m_commandPool;
	commandBufferInfo.commandBufferCount = createInfo.BufferCount;
	
	VkCommandBuffer commandBuffer;
	VK_VERIFY(vkAllocateCommandBuffers(m_pDevice->GetHandle(), &commandBufferInfo, &commandBuffer));

	return commandBuffer;
}

}