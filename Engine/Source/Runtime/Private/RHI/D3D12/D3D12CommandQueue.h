#pragma once

#include "D3D12Header.h"

#include <RHI/IRHICommandQueue.h>

namespace ow
{

struct RHICommandQueueCreateInfo;

class D3D12Device;

class D3D12CommandQueue : public IRHICommandQueue
{
public:
	D3D12CommandQueue() = delete;
	explicit D3D12CommandQueue(const D3D12Device* pDevice, const RHICommandQueueCreateInfo& createInfo);
	D3D12CommandQueue(const D3D12CommandQueue&) = delete;
	D3D12CommandQueue& operator=(const D3D12CommandQueue&) = delete;
	D3D12CommandQueue(D3D12CommandQueue&&) = default;
	D3D12CommandQueue& operator=(D3D12CommandQueue&&) = default;
	virtual ~D3D12CommandQueue() = default;

	virtual void Submit(IRHIFence* pFence) override;
	virtual void Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence) override;
	virtual void Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence, IRHISemaphore* pWaitSemaphore, IRHISemaphore* pSignalSemaphore) override;

	RefCountPtr<ID3D12CommandQueue> GetHandle() const { return m_commandQueue; }

private:
	RefCountPtr<ID3D12CommandQueue> m_commandQueue;
};

}