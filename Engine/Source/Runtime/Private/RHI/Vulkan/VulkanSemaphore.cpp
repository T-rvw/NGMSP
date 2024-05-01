#include "VulkanSemaphore.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanSemaphore::VulkanSemaphore(const VulkanDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkSemaphoreCreateInfo semaphoreCI = {};
	semaphoreCI.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(m_pDevice->GetHandle(), &semaphoreCI, nullptr, &m_semaphore);
}

VulkanSemaphore::~VulkanSemaphore()
{
	vkDestroySemaphore(m_pDevice->GetHandle(), m_semaphore, nullptr);
}

}