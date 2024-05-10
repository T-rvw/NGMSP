#include "VulkanUtils.h"

#include "VulkanHeader.h"

#include <Core/Base/CString.h>

namespace ow
{

bool VulkanUtils::FindExtension(const Vector<VkExtensionProperties>& extensions, const char* pRequireExtension)
{
	for (const auto& extension : extensions)
	{
		if (CString::Compare(extension.extensionName, pRequireExtension))
		{
			return true;
		}
	}

	return false;
}

bool VulkanUtils::FindExtensions(const Vector<VkExtensionProperties>& extensions, const Vector<const char*>& requireExtensions)
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

bool VulkanUtils::EnableExtensionSafely(Vector<const char*>& extensions, const Vector<VkExtensionProperties>& availableExtensions, const char* pRequireExtension)
{
	if (!VulkanUtils::FindExtension(availableExtensions, pRequireExtension))
	{
		return false;
	}

	extensions.push_back(pRequireExtension);
	return true;
}

bool VulkanUtils::EnableExtensionsSafely(Vector<const char*>& extensions, const Vector<VkExtensionProperties>& availableExtensions, const Vector<const char*>& requireExtensions)
{
	if (!VulkanUtils::FindExtensions(availableExtensions, requireExtensions))
	{
		return false;
	}

	for (const auto& requireExtension : requireExtensions)
	{
		extensions.push_back(requireExtension);
	}

	return true;
}

bool VulkanUtils::FindLayer(const Vector<VkLayerProperties>& layers, const char* pRequireLayer)
{
	for (const auto& layer : layers)
	{
		if (CString::Compare(layer.layerName, pRequireLayer))
		{
			return true;
		}
	}

	return false;
}

bool VulkanUtils::FindLayers(const Vector<VkLayerProperties>& layers, const Vector<const char*>& requireLayers)
{
	for (const auto& requireLayer : requireLayers)
	{
		if (!FindLayer(layers, requireLayer))
		{
			return false;
		}
	}

	return true;
}

bool VulkanUtils::EnableLayersSafely(Vector<const char*>& layers, const Vector<VkLayerProperties>& availableLayers, const char* pRequireLayer)
{
	if (!VulkanUtils::FindLayer(availableLayers, pRequireLayer))
	{
		return false;
	}

	layers.push_back(pRequireLayer);
	return true;
}

}