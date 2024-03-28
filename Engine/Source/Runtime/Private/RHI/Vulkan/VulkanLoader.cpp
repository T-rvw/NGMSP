#include "VulkanLoader.h"

#include <Core/HAL/PlatformModule.h>

namespace ow
{

PlatformModule LoadVulkanModules()
{
	PlatformModule vkDll;
	vkDll.Init("vulkan-1.dll");

	return vkDll;
}

}