#pragma once

#include "D3D12Header.h"

#include <RHI/IRHICommandBuffer.h>

namespace ow
{

class D3D12CommandBuffer : public IRHICommandBuffer
{
public:
	D3D12CommandBuffer() = default;
	D3D12CommandBuffer(const D3D12CommandBuffer&) = delete;
	D3D12CommandBuffer& operator=(const D3D12CommandBuffer&) = delete;
	D3D12CommandBuffer(D3D12CommandBuffer&&) = default;
	D3D12CommandBuffer& operator=(D3D12CommandBuffer&&) = default;
	virtual ~D3D12CommandBuffer() = default;

	virtual void Begin() override;
	virtual void End() override;
};

}