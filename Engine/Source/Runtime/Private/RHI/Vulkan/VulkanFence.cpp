#include "VulkanFence.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanFence::VulkanFence(VkDevice device, VkFence fence) :
	m_device(device),
	m_fence(fence)
{
}

VulkanFence::~VulkanFence()
{
	vkDestroyFence(m_device, m_fence, nullptr);
}

void VulkanFence::Wait(uint64 timeout)
{
	vkWaitForFences(m_device, 1, &m_fence, true, timeout);
}

void VulkanFence::Reset()
{
	vkResetFences(m_device, 1, &m_fence);
}

}