#include "D3D12SwapChain.h"

#include "D3D12CommandQueue.h"
#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12SwapChain::D3D12SwapChain(const D3D12Device* pDevice, const RHISwapChainCreateInfo& createInfo) :
	m_pDevice(pDevice),
	m_enableVSync(createInfo.PresentMode == RHIPresentMode::VSync)
{
	m_pCommandQueue = static_cast<D3D12CommandQueue*>(m_pDevice->GetCommandQueue(RHICommandType::Graphics).Get());

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
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
	BOOL allowTearing;
	D3D12_VERIFY(pDevice->GetFactory()->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(BOOL)));
	if (allowTearing)
	{
		swapChainDesc.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
	}

	RefCountPtr<IDXGISwapChain1> swapChain;
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc = {};
	fullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	fullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	fullScreenDesc.Windowed = TRUE;
	D3D12_VERIFY(m_pDevice->GetFactory()->CreateSwapChainForHwnd(m_pCommandQueue->GetHandle().Get(), (HWND)createInfo.NativeWindowHandle,
		&swapChainDesc, &fullScreenDesc, nullptr, &swapChain));
	D3D12_VERIFY(D3D12Utils::As<IDXGISwapChain4>(swapChain, &m_swapChain));

	m_backBuffers.resize(createInfo.BackBufferCount);
	for (uint32 bufferIndex = 0; bufferIndex < createInfo.BackBufferCount; ++bufferIndex)
	{
		D3D12_VERIFY(m_swapChain->GetBuffer(bufferIndex, IID_PPV_ARGS(&m_backBuffers[bufferIndex])));
	}
}

D3D12SwapChain::~D3D12SwapChain()
{
}

uint32 D3D12SwapChain::GetBackBufferCount() const
{
	return static_cast<uint32>(m_backBuffers.size());
}

void D3D12SwapChain::AcquireNextTexture(IRHISemaphore* pSemaphore)
{
	m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void D3D12SwapChain::Present(IRHISemaphore* pSemaphore)
{
	if (m_enableVSync)
	{
		m_swapChain->Present(1, 0);
	}
	else
	{
		m_swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
	}
}

}