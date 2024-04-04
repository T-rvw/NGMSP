#pragma once

#define VK_NO_PROTOTYPES
#ifdef PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <volk/volk.h>
#include <vulkan/vulkan.h>
#include <VulkanMemoryAllocator/vk_mem_alloc.h>

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