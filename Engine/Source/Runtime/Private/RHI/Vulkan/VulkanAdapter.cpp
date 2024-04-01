#include "VulkanAdapter.h"

#include "VulkanDevice.h"

#include <RHI/RHIDevice.h>

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

GPUAdapterType VulkanAdapter::GetType() const
{
	return GetInfo().Type;
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

std::unique_ptr<RHIDevice> VulkanAdapter::CreateDevice(const RHIDeviceCreateInfo& createInfo) const
{
	{
		VkPhysicalDeviceVulkan11Properties deviceProperties11{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES };
		VkPhysicalDeviceVulkan12Properties deviceProperties12{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES };
		VkPhysicalDeviceVulkan13Properties deviceProperties13{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES };
		deviceProperties11.pNext = &deviceProperties12;
		deviceProperties12.pNext = &deviceProperties13;

		VkPhysicalDeviceProperties2 deviceProperties{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
		deviceProperties.pNext = &deviceProperties11;
		vkGetPhysicalDeviceProperties2(m_physcialDevice, &deviceProperties);
	}

	{
		VkPhysicalDeviceVulkan11Features deviceFeatures11{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES };
		VkPhysicalDeviceVulkan12Features deviceFeatures12{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
		VkPhysicalDeviceVulkan13Features deviceFeatures13{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
		deviceFeatures11.pNext = &deviceFeatures12;
		deviceFeatures12.pNext = &deviceFeatures13;

		VkPhysicalDeviceFeatures2 deviceFeatures{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
		deviceFeatures.pNext = &deviceFeatures11;
		vkGetPhysicalDeviceFeatures2(m_physcialDevice, &deviceFeatures);
	}
	
	VkDeviceCreateInfo deviceCreateInfo { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };

	VkDevice vkDevice;
	vkCreateDevice(m_physcialDevice, &deviceCreateInfo, nullptr, &vkDevice);
	assert(vkDevice != VK_NULL_HANDLE);

	auto vulkanDevice = std::make_unique<VulkanDevice>(vkDevice);
	vulkanDevice->Init();

	auto device = std::make_unique<RHIDevice>();
	device->Init(MoveTemp(vulkanDevice));
	return device;
}

}