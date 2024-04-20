#include "VulkanUtils.h"

#include "VulkanHeader.h"

namespace ow
{

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

bool VulkanUtils::EnableExtensionSafely(std::vector<const char*>& extensions, const std::vector<VkExtensionProperties>& availableExtensions, const char* pRequireExtension)
{
	if (!VulkanUtils::FindExtension(availableExtensions, pRequireExtension))
	{
		return false;
	}

	extensions.push_back(pRequireExtension);
	return true;
}

bool VulkanUtils::EnableExtensionsSafely(std::vector<const char*>& extensions, const std::vector<VkExtensionProperties>& availableExtensions, const std::vector<const char*>& requireExtensions)
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

bool VulkanUtils::FindLayer(const std::vector<VkLayerProperties>& layers, const char* pRequireLayer)
{
	for (const auto& layer : layers)
	{
		if (0 == strcmp(layer.layerName, pRequireLayer))
		{
			return true;
		}
	}

	return false;
}

bool VulkanUtils::FindLayers(const std::vector<VkLayerProperties>& layers, const std::vector<const char*>& requireLayers)
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

bool VulkanUtils::EnableLayersSafely(std::vector<const char*>& layers, const std::vector<VkLayerProperties>& availableLayers, const char* pRequireLayer)
{
	if (!VulkanUtils::FindLayer(availableLayers, pRequireLayer))
	{
		return false;
	}

	layers.push_back(pRequireLayer);
	return true;
}

}