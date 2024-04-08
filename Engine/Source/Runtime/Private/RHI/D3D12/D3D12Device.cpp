#include "D3D12Device.h"

#include "D3D12CommandQueue.h"
#include "D3D12Fence.h"
#include "D3D12Semaphore.h"

#include <RHI/RHICommandQueue.h>
#include <RHI/RHIFence.h>
#include <RHI/RHISemaphore.h>

namespace ow
{

D3D12Device::D3D12Device(ID3D12Device* pDevice) :
	m_device(pDevice)
{
}

void D3D12Device::Init()
{
}

RHICommandQueue D3D12Device::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	ID3D12CommandQueue* pCommandQueue;
	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	switch (commandQueueCI.Type)
	{
	case RHICommandQueueType::Graphics:
	{
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		break;
	}
	case RHICommandQueueType::Compute:
	{
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
	}
	case RHICommandQueueType::Copy:
	{
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
	}
	default:
	{
		assert("Unsupported d3d12 command queue type.");
		break;
	}
	}
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = static_cast<int32>(commandQueueCI.Priority);
	D3D12_VERIFY(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue)));

	auto d3d12CommandQueue = std::make_unique<D3D12CommandQueue>(pCommandQueue);
	d3d12CommandQueue->SetType(commandQueueCI.Type);
	d3d12CommandQueue->Init();

	RHICommandQueue commandQueue;
	commandQueue.Reset(MoveTemp(d3d12CommandQueue));
	return commandQueue;
}

RHIFence D3D12Device::CreateFence() const
{
	ID3D12Fence* pFence;
	D3D12_VERIFY(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence)));

	auto d3d12Fence = std::make_unique<D3D12Fence>(pFence);
	d3d12Fence->Init();

	RHIFence fence;
	fence.Reset(MoveTemp(d3d12Fence));
	return fence;
}

RHISemaphore D3D12Device::CreateSemaphore(const RHISemaphoreCreateInfo& semaphoreCI) const
{
	RHISemaphore semaphore;
	return semaphore;
}

}