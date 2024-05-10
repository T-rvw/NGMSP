#pragma once

#include <Core/Container/Vector.h>
#include <RHI/RHIEnums.h>

enum VkPhysicalDeviceType;
struct VkExtensionProperties;
struct VkLayerProperties;

namespace ow
{

class VulkanUtils final
{
public:
	VulkanUtils() = delete;

	static bool FindExtension(const Vector<VkExtensionProperties>& extensions, const char* pRequireExtension);
	static bool FindExtensions(const Vector<VkExtensionProperties>& extensions, const Vector<const char*>& requireExtensions);
	static bool EnableExtensionSafely(Vector<const char*>& extensions, const Vector<VkExtensionProperties>& availableExtensions, const char* pRequireExtension);
	static bool EnableExtensionsSafely(Vector<const char*>& extensions, const Vector<VkExtensionProperties>& availableExtensions, const Vector<const char*>& requireExtensions);
	
	static bool FindLayer(const Vector<VkLayerProperties>& layers, const char* pRequireLayer);
	static bool FindLayers(const Vector<VkLayerProperties>& layers, const Vector<const char*>& requireLayers);
	static bool EnableLayersSafely(Vector<const char*>& layers, const Vector<VkLayerProperties>& availableLayers, const char* pRequireLayer);
};

}