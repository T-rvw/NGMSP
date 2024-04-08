#include "VulkanFence.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanFence::VulkanFence(VkFence fence) :
	m_fence(fence)
{
}

VulkanFence::~VulkanFence()
{
}

void VulkanFence::Init()
{
}

}