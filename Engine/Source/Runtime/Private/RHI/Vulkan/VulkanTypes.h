#pragma once

#include "VulkanHeader.h"

#include <RHI/RHITypes.h>

namespace ow
{

class VulkanTypes
{
public:
	static GPUAdapterType ToRHI(VkPhysicalDeviceType vkType);

	static VkColorSpaceKHR ToVK(RHIColorSpace rhiType);
	static VkFormat ToVK(RHIFormat rhiType);
};

}