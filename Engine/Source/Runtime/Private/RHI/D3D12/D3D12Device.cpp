#include "D3D12Device.h"

#include "D3D12Adapter.h"
#include "D3D12CommandQueue.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Device::D3D12Device(const D3D12Adapter* pAdapter, RefCountPtr<ID3D12Device> pDevice) :
	m_pAdapter(pAdapter),
	m_device(MoveTemp(pDevice))
{
}

D3D12Device::~D3D12Device()
{
}

RefCountPtr<IDXGIFactory6> D3D12Device::GetFactory() const
{
	return m_pAdapter->GetFactory();
}

RefCountPtr<ID3D12CommandQueue> D3D12Device::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI)
{
	RefCountPtr<ID3D12CommandQueue> commandQueue;

	D3D12_COMMAND_QUEUE_DESC queueDesc {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12Types::ToD3D12(commandQueueCI.Type);
	queueDesc.Priority = static_cast<int32>(commandQueueCI.Priority);
	D3D12_VERIFY(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)));

	return commandQueue;
}

RefCountPtr<ID3D12Fence> D3D12Device::CreateFence(const RHIFenceCreateInfo& createInfo) const
{
	RefCountPtr<ID3D12Fence> pFence;
	D3D12_VERIFY(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence)));

	return pFence;
}

RefCountPtr<IDXGISwapChain1> D3D12Device::CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc {};
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
	
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc {};
	fullScreenDesc.Windowed = TRUE;
	
	RefCountPtr<IDXGISwapChain1> swapChain;
	int32 typeIndex = static_cast<int32>(RHICommandType::Graphics);
	D3D12_VERIFY(GetFactory()->CreateSwapChainForHwnd(m_pCommandQueues[typeIndex]->GetHandle().Get(), (HWND)createInfo.NativeWindowHandle,
		&swapChainDesc, &fullScreenDesc, nullptr, &swapChain));

	return swapChain;
}

void D3D12Device::SetCommandQueue(const D3D12CommandQueue* pCommandQueue)
{
	int32 typeIndex = static_cast<int32>(pCommandQueue->GetType());
	m_pCommandQueues[typeIndex] = pCommandQueue;
}

void D3D12Device::ReportLiveObjects()
{
	RefCountPtr<ID3D12DebugDevice> pDebugDevice;
	D3D12_VERIFY(m_device->QueryInterface(__uuidof(ID3D12DebugDevice), reinterpret_cast<void**>(pDebugDevice.ReleaseAndGetAddressOf())));
	pDebugDevice->ReportLiveDeviceObjects((D3D12_RLDO_FLAGS)(D3D12_RLDO_IGNORE_INTERNAL | D3D12_RLDO_DETAIL));
}

}