#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIBarrier.h>

namespace ow
{

class VulkanDevice;

class VulkanBarrier : public IRHIBarrier
{
public:
	VulkanBarrier() = delete;
	explicit VulkanBarrier(const VulkanDevice* pDevice, const RHIBarrierCreateInfo& createInfo);
	VulkanBarrier(const VulkanBarrier&) = delete;
	VulkanBarrier& operator=(const VulkanBarrier&) = delete;
	VulkanBarrier(VulkanBarrier&&) = default;
	VulkanBarrier& operator=(VulkanBarrier&&) = default;
	virtual ~VulkanBarrier();
};

}