#include "VulkanUtils.h"

#include "VulkanHeader.h"

namespace ow
{

GPUAdapterType VulkanUtils::ToRHI(VkPhysicalDeviceType adapterType)
{
	switch (adapterType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
	{
		return GPUAdapterType::Discrete;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
	{
		return GPUAdapterType::Integrated;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
	{
		return GPUAdapterType::Virtual;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
	default:
	{
		return GPUAdapterType::CPU;
		break;
	}
	}

	return GPUAdapterType::CPU;
}

bool VulkanUtils::FindExtension(const std::vector<VkExtensionProperties>& extensions, const char* pRequireExtension)
{
	for (const auto& extension : extensions)
	{
		if (0 == strcmp(extension.extensionName, pRequireExtension))
		{
			return true;
		}
	}

	return false;
}

bool VulkanUtils::FindExtensions(const std::vector<VkExtensionProperties>& extensions, const std::vector<const char*>& requireExtensions)
{
	for (const auto& requireExtension : requireExtensions)
	{
		if (!FindExtension(extensions, requireExtension))
		{
			return false;
		}
	}

	return true;
}

}