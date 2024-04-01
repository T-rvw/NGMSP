#pragma once

#include <vulkan/vulkan.h>
#include <VulkanMemoryAllocator/vk_mem_alloc.h>

#include <cassert>

#define VK_VERITY(result) assert(VK_SUCCESS == result)