#pragma once

#include "D3D12Header.h"

#include <RHI/IRHISwapChain.h>

namespace ow
{

struct RHISwapChainCreateInfo;

class D3D12CommandQueue;
class D3D12Device;

class D3D12SwapChain : public IRHISwapChain
{
public:
	D3D12SwapChain() = default;
	explicit D3D12SwapChain(const D3D12Device* pDevice, const RHISwapChainCreateInfo& createInfo);
	D3D12SwapChain(const D3D12SwapChain&) = delete;
	D3D12SwapChain& operator=(const D3D12SwapChain&) = delete;
	D3D12SwapChain(D3D12SwapChain&&) = default;
	D3D12SwapChain& operator=(D3D12SwapChain&&) = default;
	virtual ~D3D12SwapChain();

	virtual uint32 GetBackBufferCount() const override;
	virtual void AcquireNextTexture(IRHISemaphore* pSemaphore) override;
	virtual void Present(IRHISemaphore* pSemaphore) override;

private:
	const D3D12Device* m_pDevice;
	const D3D12CommandQueue* m_pCommandQueue;
	bool m_enableVSync;
	RefCountPtr<IDXGISwapChain4> m_swapChain;
	Vector<RefCountPtr<ID3D12Resource>> m_backBuffers;
};

}