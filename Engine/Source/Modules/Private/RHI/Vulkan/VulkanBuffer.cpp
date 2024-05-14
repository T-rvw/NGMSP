#include "VulkanBuffer.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanBuffer::VulkanBuffer(const VulkanDevice* pDevice, const RHIBufferCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
    VkBufferCreateInfo bufferCI = {};
    bufferCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCI.size = static_cast<VkDeviceSize>(createInfo.SizeInBytes);
    bufferCI.usage = VulkanTypes::ToVK(createInfo.Usage);
    VK_VERIFY(vkCreateBuffer(m_pDevice->GetHandle(), &bufferCI, nullptr, &m_buffer));
}

VulkanBuffer::~VulkanBuffer()
{
	vkDestroyBuffer(m_pDevice->GetHandle(), m_buffer, nullptr);
}

}