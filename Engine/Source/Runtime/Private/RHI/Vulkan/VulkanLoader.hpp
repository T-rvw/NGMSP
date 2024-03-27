#pragma once

#include <Core/HAL/PlatformModule.h>

#include <vulkan.h>

namespace ow
{

static PlatformModule LoadVulkanModules()
{
	PlatformModule vkDll;
	vkDll.Init("vulkan-1.dll");

	return vkDll;
}

}