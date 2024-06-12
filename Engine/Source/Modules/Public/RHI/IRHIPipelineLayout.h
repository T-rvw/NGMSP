#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIPipelineLayout : public RefCountObject
{
public:
	virtual ~IRHIPipelineLayout() {}

	virtual PipelineStateHandle CreateComputePipelineState(const RHIComputePipelineStateCreateInfo& createInfo) = 0;
	virtual PipelineStateHandle CreateGraphicsPipelineState(const RHIGraphicsPipelineStateCreateInfo& createInfo) = 0;
	virtual PipelineStateHandle CreateRaytracingPipelineState(const RHIRaytracingPipelineStateCreateInfo& createInfo) = 0;
};

}