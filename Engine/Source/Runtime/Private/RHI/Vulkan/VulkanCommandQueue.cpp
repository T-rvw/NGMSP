#include "VulkanCommandQueue.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandQueue::VulkanCommandQueue(VkQueue queue) :
	m_queue(queue)
{
}

VulkanCommandQueue::~VulkanCommandQueue()
{
}

void VulkanCommandQueue::Init()
{
}

}