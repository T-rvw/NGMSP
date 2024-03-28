#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIBuffer.h>

namespace ow
{

class VulkanBuffer : public IRHIBuffer
{
public:
	VulkanBuffer() = default;
	VulkanBuffer(const VulkanBuffer&) = delete;
	VulkanBuffer& operator=(const VulkanBuffer&) = delete;
	VulkanBuffer(VulkanBuffer&&) = default;
	VulkanBuffer& operator=(VulkanBuffer&&) = default;
	virtual ~VulkanBuffer();

	virtual void Init() override;
};

}