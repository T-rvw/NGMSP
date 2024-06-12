#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIPipelineState.h>

namespace ow
{

class VulkanDevice;
class VulkanPipelineLayout;

class VulkanPipelineState : public IRHIPipelineState
{
public:
	VulkanPipelineState() = delete;
	VulkanPipelineState(const VulkanPipelineLayout* pLayout, const RHIComputePipelineStateCreateInfo& createInfo);
	VulkanPipelineState(const VulkanPipelineLayout* pLayout, const RHIGraphicsPipelineStateCreateInfo& createInfo);
	VulkanPipelineState(const VulkanPipelineLayout* pLayout, const RHIRaytracingPipelineStateCreateInfo& createInfo);
	VulkanPipelineState(const VulkanPipelineState&) = delete;
	VulkanPipelineState& operator=(const VulkanPipelineState&) = delete;
	VulkanPipelineState(VulkanPipelineState&&) = default;
	VulkanPipelineState& operator=(VulkanPipelineState&&) = default;
	virtual ~VulkanPipelineState();

	const VulkanDevice* GetDevice() const;
	VkPipeline GetHandle() const { return m_pipelineState; }

private:
	const VulkanPipelineLayout* m_pPipelineLayout;
	VkPipeline m_pipelineState;
};

}