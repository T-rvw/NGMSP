#include "D3D12CommandQueue.h"

#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12CommandQueue::D3D12CommandQueue(const D3D12Device* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Type = D3D12Types::ToD3D12(createInfo.Type);
	queueDesc.NodeMask = 0;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	D3D12_VERIFY(pDevice->GetHandle()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));
}

void D3D12CommandQueue::Submit(IRHIFence* pFence)
{
}

void D3D12CommandQueue::Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence)
{
}

void D3D12CommandQueue::Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence, IRHISemaphore* pWaitSemaphore, IRHISemaphore* pSignalSemaphore)
{
}

}