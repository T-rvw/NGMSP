#pragma once

#include <RHI/RHIEnums.h>

#include <vector>

enum VkPhysicalDeviceType;
struct VkExtensionProperties;

namespace ow
{

class VulkanUtils
{
public:
	static GPUAdapterType ToRHI(VkPhysicalDeviceType deviceType);
	static bool FindExtension(const std::vector<VkExtensionProperties>& extensions, const char* pRequireExtension);
	static bool FindExtensions(const std::vector<VkExtensionProperties>& extensions, const std::vector<const char*>& requireExtensions);
};

}