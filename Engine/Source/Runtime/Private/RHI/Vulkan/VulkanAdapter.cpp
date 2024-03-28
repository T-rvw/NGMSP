#include "VulkanAdapter.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanAdapter::VulkanAdapter(VkPhysicalDevice physcialDevice) :
	m_physcialDevice(physcialDevice)
{
}

VulkanAdapter::~VulkanAdapter()
{
}

void VulkanAdapter::Init()
{
}

void VulkanAdapter::SetType(VkPhysicalDeviceType deviceType)
{
	auto& info = GetInfo();

	switch (deviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
	{
		info.Type = GPUAdapterType::Discrete;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
	{
		info.Type = GPUAdapterType::Integrated;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
	{
		info.Type = GPUAdapterType::Virtual;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
	{
		info.Type = GPUAdapterType::CPU;
		break;
	}
	default:
	{
		info.Type = GPUAdapterType::Unknown;
		break;
	}
	}
}

}