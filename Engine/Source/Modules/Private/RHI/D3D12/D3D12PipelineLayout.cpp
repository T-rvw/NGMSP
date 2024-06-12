#include "D3D12PipelineLayout.h"

#include "D3D12Device.h"
#include "D3D12PipelineState.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12PipelineLayout::D3D12PipelineLayout(const D3D12Device* pDevice, const RHIPipelineLayoutCreateInfo& createInfo)
{
	//D3D12_VERIFY(pDevice->GetHandle()->CreateRootSignature(0, ));
}

PipelineStateHandle D3D12PipelineLayout::CreateComputePipelineState(const RHIComputePipelineStateCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12PipelineState>(this, createInfo);
}

PipelineStateHandle D3D12PipelineLayout::CreateGraphicsPipelineState(const RHIGraphicsPipelineStateCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12PipelineState>(this, createInfo);
}

PipelineStateHandle D3D12PipelineLayout::CreateRaytracingPipelineState(const RHIRaytracingPipelineStateCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12PipelineState>(this, createInfo);
}

}