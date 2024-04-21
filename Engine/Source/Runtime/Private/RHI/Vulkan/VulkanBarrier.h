#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIBarrier.h>

namespace ow
{

class VulkanBarrier : public IRHIBarrier
{
public:
	VulkanBarrier() = default;
	VulkanBarrier(const VulkanBarrier&) = delete;
	VulkanBarrier& operator=(const VulkanBarrier&) = delete;
	VulkanBarrier(VulkanBarrier&&) = default;
	VulkanBarrier& operator=(VulkanBarrier&&) = default;
	virtual ~VulkanBarrier();
};

}