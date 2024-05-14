#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIBuffer.h>

namespace ow
{

class VulkanDevice;

class VulkanBuffer : public IRHIBuffer
{
public:
	VulkanBuffer() = delete;
	explicit VulkanBuffer(const VulkanDevice* pDevice, const RHIBufferCreateInfo& createInfo);
	VulkanBuffer(const VulkanBuffer&) = delete;
	VulkanBuffer& operator=(const VulkanBuffer&) = delete;
	VulkanBuffer(VulkanBuffer&&) = default;
	VulkanBuffer& operator=(VulkanBuffer&&) = default;
	virtual ~VulkanBuffer();

	VkBuffer GetHandle() const { return m_buffer; }
	const VkBuffer* GetAddressOf() const { return &m_buffer; }

private:
	const VulkanDevice* m_pDevice;
	VkBuffer m_buffer;
};

}