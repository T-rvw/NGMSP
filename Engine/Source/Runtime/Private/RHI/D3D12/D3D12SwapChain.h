#pragma once

#include "D3D12Header.h"

#include <RHI/IRHISwapChain.h>

namespace ow
{

struct RHISwapChainCreateInfo;

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

	virtual uint32 GetCurrentBackBufferIndex() const override;
	virtual void AcquireNextBackBufferTexture(IRHISemaphore* pSemaphore) override;
	virtual void BeginRenderPass(IRHICommandBuffer* pCommandBuffer) override;
	virtual void EndRenderPass(IRHICommandBuffer* pCommandBuffer) override;
	virtual void Present(IRHICommandQueue* pCommandQueue, IRHISemaphore* pSemaphore) override;

private:
	RefCountPtr<IDXGISwapChain1> m_swapChain;
};

}