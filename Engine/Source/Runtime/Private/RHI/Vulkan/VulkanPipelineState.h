#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIPipelineState.h>

namespace ow
{

class VulkanDevice;

class VulkanPipelineState : public IRHIPipelineState
{
public:
	VulkanPipelineState() = delete;
	VulkanPipelineState(const VulkanDevice* pDevice, const RHIComputePipelineStateCreateInfo& createInfo);
	VulkanPipelineState(const VulkanDevice* pDevice, const RHIGraphicsPipelineStateCreateInfo& createInfo);
	VulkanPipelineState(const VulkanDevice* pDevice, const RHIRaytracingPipelineStateCreateInfo& createInfo);
	VulkanPipelineState(const VulkanPipelineState&) = delete;
	VulkanPipelineState& operator=(const VulkanPipelineState&) = delete;
	VulkanPipelineState(VulkanPipelineState&&) = default;
	VulkanPipelineState& operator=(VulkanPipelineState&&) = default;
	virtual ~VulkanPipelineState();

	VkPipeline GetHandle() const { return m_pipelineState; }

private:
	const VulkanDevice* m_pDevice;
	VkPipeline m_pipelineState;
};

}