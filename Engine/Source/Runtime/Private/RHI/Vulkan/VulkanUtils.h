#pragma once

#include <RHI/RHIEnums.h>

#include <vector>

enum VkPhysicalDeviceType;
struct VkExtensionProperties;
struct VkLayerProperties;

namespace ow
{

class VulkanUtils
{
public:
	static GPUAdapterType ToRHI(VkPhysicalDeviceType deviceType);

	static bool FindExtension(const std::vector<VkExtensionProperties>& extensions, const char* pRequireExtension);
	static bool FindExtensions(const std::vector<VkExtensionProperties>& extensions, const std::vector<const char*>& requireExtensions);
	static bool EnableExtensionSafely(std::vector<const char*>& extensions, const std::vector<VkExtensionProperties>& availableExtensions, const char* pRequireExtension);
	static bool EnableExtensionsSafely(std::vector<const char*>& extensions, const std::vector<VkExtensionProperties>& availableExtensions, const std::vector<const char*>& requireExtensions);
	
	static bool FindLayer(const std::vector<VkLayerProperties>& layers, const char* pRequireLayer);
	static bool FindLayers(const std::vector<VkLayerProperties>& layers, const std::vector<const char*>& requireLayers);
	static bool EnableLayersSafely(std::vector<const char*>& layers, const std::vector<VkLayerProperties>& availableLayers, const char* pRequireLayer);
};

}