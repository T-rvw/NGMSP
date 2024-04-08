#pragma once

#define VK_NO_PROTOTYPES
#ifdef PLATFORM_WINDOWS
#include "../../Core/HAL/Windows/WindowsUndefines.h"
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <volk/volk.h>
#include <vulkan/vulkan.h>
#include <VulkanMemoryAllocator/vk_mem_alloc.h>

#ifdef PLATFORM_WINDOWS
// Undef windows macros which will affect RHI interfaces.
#undef CreateSemaphore
#endif

#include <cassert>

#define VK_VERIFY(result) \
	do \
	{ \
		if (VK_SUCCESS != result) \
		{ \
			printf("Vulkan failure : %s\n", ow::EnumName<VkResult>(result).data()); \
			assert(false); \
		} \
	} while (false)