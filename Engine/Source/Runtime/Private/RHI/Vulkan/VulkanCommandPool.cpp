#include "VulkanCommandPool.h"

#include "VulkanCommandBuffer.h"
#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandPool::VulkanCommandPool(const VulkanDevice* pDevice, const RHICommandPoolCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkCommandPoolCreateInfo commandPoolCI {};
	commandPoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCI.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandPoolCI.queueFamilyIndex = createInfo.QueueID;
	VK_VERIFY(vkCreateCommandPool(pDevice->GetHandle(), &commandPoolCI, nullptr, &m_commandPool));
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(m_pDevice->GetHandle(), m_commandPool, nullptr);
}

RefCountPtr<IRHICommandBuffer> VulkanCommandPool::CreateCommandBuffer(const RHICommandBufferCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanCommandBuffer>(this, createInfo);
}

}