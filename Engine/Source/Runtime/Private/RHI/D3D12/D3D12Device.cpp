#include "D3D12Device.h"

#include "D3D12CommandQueue.h"
#include "D3D12Fence.h"
#include "D3D12Instance.h"
#include "D3D12Semaphore.h"
#include "D3D12SwapChain.h"

#include <RHI/IRHICommandQueue.h>
#include <RHI/IRHIFence.h>
#include <RHI/IRHIInstance.h>
#include <RHI/IRHISemaphore.h>
#include <RHI/IRHISwapChain.h>

namespace ow
{

D3D12Device::D3D12Device(ComPtr<ID3D12Device> pDevice) :
	m_device(MoveTemp(pDevice))
{
}

ComPtr<ID3D12CommandQueue> D3D12Device::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	int32 typeIndex = static_cast<int32>(commandQueueCI.Type);
	ComPtr<ID3D12CommandQueue> pCommandQueue = m_commandQueues[typeIndex].Get();

	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = ToD3D12(commandQueueCI.Type);
	queueDesc.Priority = static_cast<int32>(commandQueueCI.Priority);
	D3D12_VERIFY(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue)));

	return pCommandQueue;
}

ComPtr<ID3D12Fence> D3D12Device::CreateFence() const
{
	ComPtr<ID3D12Fence> pFence;
	D3D12_VERIFY(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence)));

	return pFence;
}

ComPtr<IDXGISwapChain1> D3D12Device::CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const
{
	//ComPtr<IDXGIFactory4> pDXGIFactory = static_cast<IDXGIFactory4*>(createInfo.Instance->GetHandle());
	//
	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc {};
	//swapChainDesc.Width = createInfo.BackBufferWidth;
	//swapChainDesc.Height = createInfo.BackBufferHeight;
	//swapChainDesc.Format = ToD3D12(createInfo.Format);
	//swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//swapChainDesc.BufferCount = createInfo.BackBufferCount;
	//swapChainDesc.SampleDesc.Count = 1;
	//swapChainDesc.SampleDesc.Quality = 0;
	//swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	//swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
	//
	//DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc {};
	//fsSwapChainDesc.Windowed = TRUE;
	//
	//int32 typeIndex = static_cast<int32>(RHICommandType::Graphics);
	//ID3D12CommandQueue* pDirectCommandQueue = m_commandQueues[typeIndex].Get();
	
	ComPtr<IDXGISwapChain1> swapChain;
	//D3D12_VERIFY(pDXGIFactory->CreateSwapChainForHwnd(pDirectCommandQueue, (HWND)createInfo.NativeWindowHandle,
	//	&swapChainDesc, &fsSwapChainDesc, nullptr, &swapChain));

	return swapChain;
}

}