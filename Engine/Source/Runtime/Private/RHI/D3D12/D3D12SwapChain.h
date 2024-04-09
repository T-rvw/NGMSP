#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHISwapChain.h>

namespace ow
{

class D3D12SwapChain : public IRHISwapChain
{
public:
	D3D12SwapChain() = default;
	D3D12SwapChain(const D3D12SwapChain&) = delete;
	D3D12SwapChain& operator=(const D3D12SwapChain&) = delete;
	D3D12SwapChain(D3D12SwapChain&&) = default;
	D3D12SwapChain& operator=(D3D12SwapChain&&) = default;
	virtual ~D3D12SwapChain() = default;

	virtual std::vector<RHITexture> GetBackBufferTextures() const override;
};

}