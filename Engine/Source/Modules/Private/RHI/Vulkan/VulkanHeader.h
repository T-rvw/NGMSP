#pragma once

#ifdef PLATFORM_WINDOWS
#include "../../Core/HAL/Windows/WindowsUndefines.h"
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define VK_NO_PROTOTYPES
#include <volk/volk.h>
#include <vulkan/vulkan.h>
#include <VulkanMemoryAllocator/vk_mem_alloc.h>

#include "VulkanTypes.h"
#include "VulkanUtils.h"

#include <Core/Base/Assert.h>
#include <Core/Base/RefCountPtr.h>
#include <Core/Base/TypeTraits.h>

#include <memory>

#define VK_VERIFY(result) \
	do \
	{ \
		if (VK_SUCCESS != result) \
		{ \
			printf("Vulkan failure : %s\n", ow::EnumName<VkResult>(result).data()); \
			Assert(false); \
		} \
	} while (false)