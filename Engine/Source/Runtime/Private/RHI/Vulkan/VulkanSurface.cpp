#include "VulkanSurface.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanSurface::VulkanSurface(VkInstance instance, VkSurfaceKHR surface) :
	m_instance(instance),
	m_surface(surface)
{
}

VulkanSurface::~VulkanSurface()
{
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

void* VulkanSurface::GetHandle() const
{
	return m_surface;
}

}