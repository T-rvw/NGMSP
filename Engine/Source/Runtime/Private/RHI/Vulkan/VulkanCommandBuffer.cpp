#include "VulkanCommandBuffer.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandBuffer::VulkanCommandBuffer(VkCommandBuffer commandBuffer) :
	m_commandBuffer(commandBuffer)
{
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
}

}