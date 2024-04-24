#include "D3D12SwapChain.h"

#include "D3D12CommandQueue.h"
#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12SwapChain::D3D12SwapChain(const D3D12Device* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = createInfo.BackBufferWidth;
	swapChainDesc.Height = createInfo.BackBufferHeight;
	swapChainDesc.Format = D3D12Types::ToD3D12(createInfo.Format);
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = createInfo.BackBufferCount;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	const auto* pGraphicsCommandQueue = pDevice->GetCommandQueue(RHICommandType::Graphics);

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc {};
	fullScreenDesc.Windowed = TRUE;
	D3D12_VERIFY(pDevice->GetFactory()->CreateSwapChainForHwnd(pGraphicsCommandQueue->GetHandle().Get(), (HWND)createInfo.NativeWindowHandle,
		&swapChainDesc, &fullScreenDesc, nullptr, &m_swapChain));
}

D3D12SwapChain::~D3D12SwapChain()
{
}

}