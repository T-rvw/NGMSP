#include "D3D12Device.h"

#include "D3D12CommandQueue.h"

#include <RHI/RHICommandQueue.h>

namespace ow
{

D3D12Device::D3D12Device(ID3D12Device* pDevice) :
	m_device(pDevice)
{
}

void D3D12Device::Init()
{
}

RHICommandQueue D3D12Device::CreateCommandQueue(RHICommandQueueCreateInfo commandQueueCI) const
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
	m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue));

	auto d3d12CommandQueue = std::make_unique<D3D12CommandQueue>(pCommandQueue);
	d3d12CommandQueue->SetType(commandQueueCI.Type);
	d3d12CommandQueue->Init();

	RHICommandQueue commandQueue;
	commandQueue.Reset(MoveTemp(d3d12CommandQueue));
	return commandQueue;
}

}