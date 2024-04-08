#include "VulkanSemaphore.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanSemaphore::VulkanSemaphore(VkSemaphore semaphore) :
	m_semaphore(semaphore)
{
}

VulkanSemaphore::~VulkanSemaphore()
{
}

void VulkanSemaphore::Init()
{
}

}