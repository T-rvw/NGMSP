#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHISurface.h>

namespace ow
{

class VulkanSurface : public IRHISurface
{
public:
	VulkanSurface() = default;
	explicit VulkanSurface(VkInstance instance, VkSurfaceKHR surface);
	VulkanSurface(const VulkanSurface&) = delete;
	VulkanSurface& operator=(const VulkanSurface&) = delete;
	VulkanSurface(VulkanSurface&&) = default;
	VulkanSurface& operator=(VulkanSurface&&) = default;
	virtual ~VulkanSurface();

	virtual void* GetHandle() const override;

private:
	VkInstance m_instance = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
};

}