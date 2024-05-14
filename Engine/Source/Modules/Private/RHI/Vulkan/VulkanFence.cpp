#include "VulkanFence.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanFence::VulkanFence(const VulkanDevice* pDevice, const RHIFenceCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkFenceCreateInfo fenceCI = {};
	fenceCI.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCI.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	VK_VERIFY(vkCreateFence(m_pDevice->GetHandle(), &fenceCI, nullptr, &m_fence));
}

VulkanFence::~VulkanFence()
{
	vkDestroyFence(m_pDevice->GetHandle(), m_fence, nullptr);
}

uint64 VulkanFence::Signal(uint64 fenceCount)
{
	return 0;
}

void VulkanFence::Wait(uint64 fenceCount)
{
	Wait(fenceCount, UINT64_MAX);
}

void VulkanFence::Wait(uint64 fenceCount, uint64 timeout)
{
	vkWaitForFences(m_pDevice->GetHandle(), static_cast<uint32>(fenceCount), &m_fence, VK_TRUE, timeout);
}

bool VulkanFence::IsComplete(uint64 fenceCount)
{
	return true;
}

void VulkanFence::Reset(uint64 fenceCount)
{
	vkResetFences(m_pDevice->GetHandle(), static_cast<uint32>(fenceCount), &m_fence);
}

}