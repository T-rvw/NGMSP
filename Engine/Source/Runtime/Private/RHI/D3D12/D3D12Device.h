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
	explicit D3D12Device(ID3D12Device* pDevice);
	D3D12Device(const D3D12Device&) = delete;
	D3D12Device& operator=(const D3D12Device&) = delete;
	D3D12Device(D3D12Device&&) = default;
	D3D12Device& operator=(D3D12Device&&) = default;
	virtual ~D3D12Device() = default;

	virtual void* GetHandle() const override { return m_device.Get(); }
	virtual IRHICommandQueue* CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const override;
	virtual IRHIFence* CreateFence() const override;
	virtual IRHISemaphore* CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const override;
	virtual IRHISwapChain* CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const override;

private:
	ComPtr<ID3D12CommandQueue> m_commandQueues[EnumCount<RHICommandType>()];
	ComPtr<ID3D12Device> m_device;
};

}