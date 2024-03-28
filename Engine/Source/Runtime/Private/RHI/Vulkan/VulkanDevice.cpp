#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

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

}