#include "VulkanFence.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanFence::VulkanFence(const VulkanDevice* pDevice, const RHIFenceCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkFenceCreateInfo fenceCI{};
	fenceCI.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	VK_VERIFY(vkCreateFence(m_pDevice->GetHandle(), &fenceCI, nullptr, &m_fence));
}

VulkanFence::~VulkanFence()
{
	vkDestroyFence(m_pDevice->GetHandle(), m_fence, nullptr);
}

uint64 VulkanFence::Signal(uint64 fenceValue)
{
	return 0;
}

void VulkanFence::Wait(uint64 timeout)
{
	vkWaitForFences(m_pDevice->GetHandle(), 1, &m_fence, true, timeout);
}

bool VulkanFence::IsComplete(uint64 fenceValue)
{
	return true;
}

void VulkanFence::Reset()
{
	vkResetFences(m_pDevice->GetHandle(), 1, &m_fence);
}

}