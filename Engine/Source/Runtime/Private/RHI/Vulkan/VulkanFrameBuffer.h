#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIFramebuffer.h>

namespace ow
{

class VulkanFramebuffer : public IRHIFramebuffer
{
public:
	VulkanFramebuffer() = default;
	explicit VulkanFramebuffer(VkFramebuffer framebuffer);
	VulkanFramebuffer(const VulkanFramebuffer&) = delete;
	VulkanFramebuffer& operator=(const VulkanFramebuffer&) = delete;
	VulkanFramebuffer(VulkanFramebuffer&&) = default;
	VulkanFramebuffer& operator=(VulkanFramebuffer&&) = default;
	virtual ~VulkanFramebuffer();

private:
	VkFramebuffer m_framebuffer = VK_NULL_HANDLE;
};

}