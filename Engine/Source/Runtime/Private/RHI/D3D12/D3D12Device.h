#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIDevice.h>

namespace ow
{

class IRHICommandQueue;
class IRHIFence;
class IRHISemaphore;
class IRHISwapChain;

class D3D12Device : public IRHIDevice
{
public:
	D3D12Device() = default;
	explicit D3D12Device(ComPtr<ID3D12Device> pDevice);
	D3D12Device(const D3D12Device&) = delete;
	D3D12Device& operator=(const D3D12Device&) = delete;
	D3D12Device(D3D12Device&&) = default;
	D3D12Device& operator=(D3D12Device&&) = default;
	virtual ~D3D12Device() = default;

private:
	ComPtr<ID3D12CommandQueue> CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const;
	ComPtr<ID3D12Fence> CreateFence() const;
	ComPtr<IDXGISwapChain1> CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const;

private:
	friend class D3D12RHIModule;
	ComPtr<ID3D12CommandQueue> m_commandQueues[EnumCount<RHICommandType>()];
	ComPtr<ID3D12Device> m_device;
};

}