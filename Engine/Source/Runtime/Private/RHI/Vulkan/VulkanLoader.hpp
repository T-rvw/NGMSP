#pragma once

#include "VulkanHeader.h"

#include <Core/HAL/PlatformModule.h>

namespace ow
{

static PlatformModule LoadVulkanModules()
{
	PlatformModule vkDll;
	vkDll.Init("vulkan-1.dll");

	return vkDll;
}

}