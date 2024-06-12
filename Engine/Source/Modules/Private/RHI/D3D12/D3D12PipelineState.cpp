#include "D3D12PipelineState.h"

#include "D3D12PipelineLayout.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12PipelineState::D3D12PipelineState(const D3D12PipelineLayout* pLayout, const RHIComputePipelineStateCreateInfo& createInfo)
{
}

D3D12PipelineState::D3D12PipelineState(const D3D12PipelineLayout* pLayout, const RHIGraphicsPipelineStateCreateInfo& createInfo)
{
}

D3D12PipelineState::D3D12PipelineState(const D3D12PipelineLayout* pLayout, const RHIRaytracingPipelineStateCreateInfo& createInfo)
{
}

}