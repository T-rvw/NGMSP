#include "VulkanDevice.h"

#include <RHI/RHIDevice.h>

namespace ow
{

VulkanDevice::VulkanDevice(VkDevice device) :
	m_device(device)
{
}

VulkanDevice::~VulkanDevice()
{
	if (m_device != VK_NULL_HANDLE)
	{
		vkDestroyDevice(m_device, nullptr);
		m_device = VK_NULL_HANDLE;
	}
}

void VulkanDevice::Init()
{
}

bool VulkanDevice::CheckFeatrue(RHIFeatrueFlags flags) const
{
	return false;
}

}