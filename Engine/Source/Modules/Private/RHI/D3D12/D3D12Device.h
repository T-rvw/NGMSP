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

	virtual BarrierHandle CreateBarrier(const RHIBarrierCreateInfo& createInfo) override;
	virtual BufferHandle CreateBuffer(const RHIBufferCreateInfo& createInfo) override;
	virtual CommandPoolHandle CreateCommandPool(const RHICommandPoolCreateInfo& createInfo) override;
	virtual FenceHandle CreateFence(const RHIFenceCreateInfo& createInfo) override;
	virtual PipelineLayoutHandle CreatePipelineLayout(const RHIPipelineLayoutCreateInfo& createInfo) override;
	virtual SemaphoreHandle CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) override;
	virtual SwapChainHandle CreateSwapChain(const RHISwapChainCreateInfo& createInfo) override;
	virtual TextureHandle CreateTexture(const RHITextureCreateInfo& createInfo) override;
	virtual CommandQueueHandle GetCommandQueue(RHICommandType commandType) const;
	
private:
	void ReportLiveObjects();

private:
	const D3D12Adapter* m_pAdapter;

	RefCountPtr<ID3D12Device5> m_device;
	RefCountPtr<D3D12CommandQueue> m_commandQueues[EnumCount<RHICommandType>()];
};

}