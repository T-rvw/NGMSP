#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIPipelineState.h>

namespace ow
{

class D3D12PipelineLayout;

class D3D12PipelineState : public IRHIPipelineState
{
public:
	D3D12PipelineState() = delete;
	D3D12PipelineState(const D3D12PipelineLayout* pLayout, const RHIComputePipelineStateCreateInfo& createInfo);
	D3D12PipelineState(const D3D12PipelineLayout* pLayout, const RHIGraphicsPipelineStateCreateInfo& createInfo);
	D3D12PipelineState(const D3D12PipelineLayout* pLayout, const RHIRaytracingPipelineStateCreateInfo& createInfo);
	D3D12PipelineState(const D3D12PipelineState&) = delete;
	D3D12PipelineState& operator=(const D3D12PipelineState&) = delete;
	D3D12PipelineState(D3D12PipelineState&&) = default;
	D3D12PipelineState& operator=(D3D12PipelineState&&) = default;
	virtual ~D3D12PipelineState() = default;

private:
	RefCountPtr<ID3D12PipelineState> m_pipelineState;
};

}