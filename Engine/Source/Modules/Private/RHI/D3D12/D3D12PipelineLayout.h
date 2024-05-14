#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIPipelineLayout.h>

namespace ow
{

class D3D12Device;

class D3D12PipelineLayout : public IRHIPipelineLayout
{
public:
	D3D12PipelineLayout() = delete;
	D3D12PipelineLayout(const D3D12Device* pDevice, const RHIPipelineLayoutCreateInfo& createInfo);
	D3D12PipelineLayout(const D3D12PipelineLayout&) = delete;
	D3D12PipelineLayout& operator=(const D3D12PipelineLayout&) = delete;
	D3D12PipelineLayout(D3D12PipelineLayout&&) = default;
	D3D12PipelineLayout& operator=(D3D12PipelineLayout&&) = default;
	virtual ~D3D12PipelineLayout() = default;

private:
	RefCountPtr<ID3D12RootSignature> m_rootSignature;
};

}