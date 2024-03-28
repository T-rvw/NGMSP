#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHICommandPool.h>

namespace ow
{

class VulkanCommandPool : public IRHICommandPool
{
public:
	VulkanCommandPool() = default;
	VulkanCommandPool(const VulkanCommandPool&) = delete;
	VulkanCommandPool& operator=(const VulkanCommandPool&) = delete;
	VulkanCommandPool(VulkanCommandPool&&) = default;
	VulkanCommandPool& operator=(VulkanCommandPool&&) = default;
	virtual ~VulkanCommandPool();

	virtual void Init() override;
};

}