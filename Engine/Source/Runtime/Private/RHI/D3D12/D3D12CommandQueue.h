#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHICommandQueue.h>

namespace ow
{

class D3D12CommandQueue : public IRHICommandQueue
{
public:
	D3D12CommandQueue() = default;
	D3D12CommandQueue(const D3D12CommandQueue&) = delete;
	D3D12CommandQueue& operator=(const D3D12CommandQueue&) = delete;
	D3D12CommandQueue(D3D12CommandQueue&&) = default;
	D3D12CommandQueue& operator=(D3D12CommandQueue&&) = default;
	virtual ~D3D12CommandQueue() = default;

	void Init();

private:
	ComPtr<ID3D12CommandQueue> m_commandQueue;
};

}