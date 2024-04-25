#include "VulkanBuffer.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanBuffer::VulkanBuffer(const VulkanDevice* pDevice, const RHIBufferCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
}

VulkanBuffer::~VulkanBuffer()
{
	vkDestroyBufferView(m_pDevice->GetHandle(), m_bufferView, nullptr);
	vkDestroyBuffer(m_pDevice->GetHandle(), m_buffer, nullptr);
}

}