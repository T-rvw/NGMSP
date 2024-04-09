#include "VulkanFramebuffer.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanFramebuffer::VulkanFramebuffer(VkFramebuffer framebuffer) :
	m_framebuffer(framebuffer)
{
}

VulkanFramebuffer::~VulkanFramebuffer()
{
}

}