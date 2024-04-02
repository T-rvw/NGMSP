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
	vkDestroyDevice(m_device, nullptr);
}

void VulkanDevice::Init()
{
}

}