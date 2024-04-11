#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandBuffer.h>

namespace ow
{

class VulkanCommandBuffer : public IRHICommandBuffer
{
public:
	VulkanCommandBuffer() = default;
	VulkanCommandBuffer(const VulkanCommandBuffer&) = delete;
	VulkanCommandBuffer& operator=(const VulkanCommandBuffer&) = delete;
	VulkanCommandBuffer(VulkanCommandBuffer&&) = default;
	VulkanCommandBuffer& operator=(VulkanCommandBuffer&&) = default;
	virtual ~VulkanCommandBuffer();

	virtual void Init() override;
};

}