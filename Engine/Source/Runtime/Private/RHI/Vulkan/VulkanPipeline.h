#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIPipeline.h>

namespace ow
{

class VulkanPipeline : public IRHIPipeline
{
public:
	VulkanPipeline() = default;
	VulkanPipeline(const VulkanPipeline&) = delete;
	VulkanPipeline& operator=(const VulkanPipeline&) = delete;
	VulkanPipeline(VulkanPipeline&&) = default;
	VulkanPipeline& operator=(VulkanPipeline&&) = default;
	virtual ~VulkanPipeline();
};

}