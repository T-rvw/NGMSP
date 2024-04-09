#include "D3D12Device.h"

#include "D3D12CommandQueue.h"
#include "D3D12Fence.h"
#include "D3D12Instance.h"
#include "D3D12Semaphore.h"
#include "D3D12SwapChain.h"

#include <RHI/RHICommandQueue.h>
#include <RHI/RHIFence.h>
#include <RHI/RHIInstance.h>
#include <RHI/RHISemaphore.h>
#include <RHI/RHISwapChain.h>

namespace ow
{

D3D12Device::D3D12Device(ID3D12Device* pDevice) :
	m_device(pDevice)
{
}

RHICommandQueue D3D12Device::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	int32 typeIndex = static_cast<int32>(commandQueueCI.Type);
	ID3D12CommandQueue* pCommandQueue = m_commandQueues[typeIndex].Get();

	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = ToD3D12(commandQueueCI.Type);
	queueDesc.Priority = static_cast<int32>(commandQueueCI.Priority);
	D3D12_VERIFY(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue)));

	auto d3d12CommandQueue = std::make_unique<D3D12CommandQueue>(pCommandQueue);
	d3d12CommandQueue->SetType(commandQueueCI.Type);

	RHICommandQueue commandQueue;
	commandQueue.Reset(MoveTemp(d3d12CommandQueue));
	return commandQueue;
}

RHIFence D3D12Device::CreateFence() const
{
	ID3D12Fence* pFence;
	D3D12_VERIFY(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence)));

	auto d3d12Fence = std::make_unique<D3D12Fence>(m_device.Get(), pFence);

	RHIFence fence;
	fence.Reset(MoveTemp(d3d12Fence));
	return fence;
}

RHISemaphore D3D12Device::CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const
{
	RHISemaphore semaphore;
	return semaphore;
}

RHISwapChain D3D12Device::CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const
{
	ComPtr<IDXGIFactory4> pDXGIFactory = static_cast<IDXGIFactory4*>(createInfo.Instance->GetHandle());

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc {};
	swapChainDesc.Width = createInfo.BackBufferWidth;
	swapChainDesc.Height = createInfo.BackBufferHeight;
	swapChainDesc.Format = ToD3D12(createInfo.Format);
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = createInfo.BackBufferCount;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc {};
	fsSwapChainDesc.Windowed = TRUE;

	int32 typeIndex = static_cast<int32>(RHICommandType::Graphics);
	ID3D12CommandQueue* pDirectCommandQueue = m_commandQueues[typeIndex].Get();

	ComPtr<IDXGISwapChain1> swapChain;
	D3D12_VERIFY(pDXGIFactory->CreateSwapChainForHwnd(pDirectCommandQueue, (HWND)createInfo.NativeWindowHandle,
		&swapChainDesc, &fsSwapChainDesc, nullptr, &swapChain));

	RHISwapChain rhiSwapChain;
	rhiSwapChain.Reset(std::make_unique<D3D12SwapChain>(swapChain.Get()));
	return rhiSwapChain;
}

}