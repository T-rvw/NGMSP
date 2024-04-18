#pragma once

#include "D3D12Header.h"

#include <RHI/IRHICommandQueue.h>

namespace ow
{

class D3D12CommandQueue : public IRHICommandQueue
{
public:
	D3D12CommandQueue() = default;
	explicit D3D12CommandQueue(ComPtr<ID3D12CommandQueue> pCommandQueue);
	D3D12CommandQueue(const D3D12CommandQueue&) = delete;
	D3D12CommandQueue& operator=(const D3D12CommandQueue&) = delete;
	D3D12CommandQueue(D3D12CommandQueue&&) = default;
	D3D12CommandQueue& operator=(D3D12CommandQueue&&) = default;
	virtual ~D3D12CommandQueue() = default;

private:
	friend class D3D12RHIModule;

private:
	ComPtr<ID3D12CommandQueue> m_commandQueue;
};

}