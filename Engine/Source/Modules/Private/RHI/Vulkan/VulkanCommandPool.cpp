#include "VulkanCommandPool.h"

#include "VulkanCommandList.h"
#include "VulkanCommandQueue.h"
#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandPool::VulkanCommandPool(const VulkanDevice* pDevice, const RHICommandPoolCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	auto* pVulkanCommandQueue = static_cast<VulkanCommandQueue*>(m_pDevice->GetCommandQueue(createInfo.Type).Get());

	VkCommandPoolCreateInfo commandPoolCI = {};
	commandPoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCI.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandPoolCI.queueFamilyIndex = pVulkanCommandQueue->GetFamilyIndex();
	VK_VERIFY(vkCreateCommandPool(pDevice->GetHandle(), &commandPoolCI, nullptr, &m_commandPool));
}

VulkanCommandPool::~VulkanCommandPool()
{
	vkDestroyCommandPool(m_pDevice->GetHandle(), m_commandPool, nullptr);
}

CommandListHandle VulkanCommandPool::CreateCommandList(const RHICommandListCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanCommandList>(this, createInfo);
}

}