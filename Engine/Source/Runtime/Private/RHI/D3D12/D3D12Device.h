#pragma once

#include "D3D12Header.h"

#include <Core/Base/NameOf.h>
#include <RHI/IRHIDevice.h>

namespace ow
{

struct RHIDeviceCreateInfo;

class D3D12Adapter;
class D3D12CommandQueue;

class D3D12Device : public IRHIDevice
{
public:
	D3D12Device() = default;
	explicit D3D12Device(const D3D12Adapter* pAdapter, const RHIDeviceCreateInfo& createInfo);
	D3D12Device(const D3D12Device&) = delete;
	D3D12Device& operator=(const D3D12Device&) = delete;
	D3D12Device(D3D12Device&&) = default;
	D3D12Device& operator=(D3D12Device&&) = default;
	virtual ~D3D12Device() = default;

	RefCountPtr<ID3D12Device5> GetHandle() const { return m_device; }
	RefCountPtr<IDXGIFactory6> GetFactory() const;
	const D3D12CommandQueue* GetCommandQueue(RHICommandType commandType) const;

	virtual RefCountPtr<IRHISwapChain> CreateSwapChain(const RHISwapChainCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandPool> CreateCommandPool(const RHICommandPoolCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHICommandQueue> CreateCommandQueue(const RHICommandQueueCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBarrier> CreateBarrier(const RHIBarrierCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIFence> CreateFence(const RHIFenceCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHISemaphore> CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHIBuffer> CreateBuffer(const RHIBufferCreateInfo& createInfo) override;
	virtual RefCountPtr<IRHITexture> CreateTexture(const RHITextureCreateInfo& createInfo) override;

private:
	void SetCommandQueue(const D3D12CommandQueue* pCommandQueue);
	void ReportLiveObjects();

private:
	RefCountPtr<ID3D12Device5> m_device;
	const D3D12CommandQueue* m_pCommandQueues[EnumCount<RHICommandType>()];
	const D3D12Adapter* m_pAdapter = nullptr;
};

}