#pragma once

#include "VulkanHeader.h"

#include <RHI/RHITypes.h>

namespace ow
{

class VulkanTypes
{
public:
	static GPUAdapterType ToRHI(VkPhysicalDeviceType vkType);

	static VkSamplerAddressMode ToVK(RHIAddressMode rhiType);
	static VkBufferUsageFlags ToVK(RHIBufferUsage rhiType);
	static VkColorSpaceKHR ToVK(RHIColorSpace rhiType);
	static VkCullModeFlagBits ToVK(RHICullMode rhiType);
	static VkFilter ToVK(RHIFilter rhiType);
	static VkFormat ToVK(RHIFormat rhiType);
	static VkFrontFace ToVK(RHIFrontFace rhiType);
	static VkSamplerMipmapMode ToVK(RHIMipmapMode rhiType);
	static VkPolygonMode ToVK(RHIPolygonMode rhiType);
	static VkPrimitiveTopology ToVK(RHIPrimitiveTopology rhiType);
	static VkShaderStageFlagBits ToVK(RHIShaderStage rhiType);
	static VkImageViewType ToVK(RHITextureType rhiType);
	static VkImageUsageFlags ToVK(RHITextureUsage rhiType);
};

}