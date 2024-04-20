#pragma once

#include "D3D12Header.h"

#include <Core/Base/NameOf.h>
#include <RHI/IRHIDevice.h>

namespace ow
{

struct RHICommandQueueCreateInfo;
struct RHIFenceCreateInfo;
struct RHISwapChainCreateInfo;

class D3D12Adapter;
class D3D12CommandQueue;

class D3D12Device : public IRHIDevice
{
public:
	D3D12Device() = default;
	explicit D3D12Device(const D3D12Adapter* pAdapter, ComPtr<ID3D12Device> pDevice);
	D3D12Device(const D3D12Device&) = delete;
	D3D12Device& operator=(const D3D12Device&) = delete;
	D3D12Device(D3D12Device&&) = default;
	D3D12Device& operator=(D3D12Device&&) = default;
	virtual ~D3D12Device();

	ComPtr<IDXGIFactory6> GetFactory() const;

private:
	friend class D3D12RHIModule;
	ComPtr<ID3D12CommandQueue> CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI);
	ComPtr<ID3D12Fence> CreateFence(const RHIFenceCreateInfo& createInfo) const;
	ComPtr<IDXGISwapChain1> CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const;
	void SetCommandQueue(const D3D12CommandQueue* pCommandQueue);
	void ReportLiveObjects();

private:
	ComPtr<ID3D12Device> m_device;
	const D3D12CommandQueue* m_pCommandQueues[EnumCount<RHICommandType>()];
	const D3D12Adapter* m_pAdapter = nullptr;
};

}