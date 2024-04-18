#include "VulkanDevice.h"

#include "VulkanCommandQueue.h"
#include "VulkanInstance.h"
#include "VulkanSemaphore.h"

#include <RHI/IRHICommandQueue.h>
#include <RHI/IRHIInstance.h>
#include <RHI/IRHISemaphore.h>

namespace ow
{

VulkanDevice::VulkanDevice(const VulkanAdapter* pAdapter, VkDevice device) :
	m_pAdapter(pAdapter),
	m_device(device)
{
}

VulkanDevice::~VulkanDevice()
{
	vkDestroyDevice(m_device, nullptr);
}

VkPhysicalDevice VulkanDevice::GetAdapter() const
{
	return m_pAdapter->GetHandle();
}

VkInstance VulkanDevice::GetInstance() const
{
	return m_pAdapter->GetInstance();
}

VkQueue VulkanDevice::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	VkQueue vkCommandQueue;
	vkGetDeviceQueue(m_device, commandQueueCI.ID, 0, &vkCommandQueue);

	return vkCommandQueue;
}

VkSemaphore VulkanDevice::CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const
{
	VkSemaphore semaphore {};
	return semaphore;
}

}