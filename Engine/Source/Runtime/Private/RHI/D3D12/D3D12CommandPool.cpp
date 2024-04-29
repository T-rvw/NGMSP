#include "D3D12CommandPool.h"

#include "D3D12CommandBuffer.h"
#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12CommandPool::D3D12CommandPool(const D3D12Device* pDevice, const RHICommandPoolCreateInfo& createInfo)
{
	D3D12_VERIFY(pDevice->GetHandle()->CreateCommandAllocator(D3D12Types::ToD3D12(createInfo.Type), IID_PPV_ARGS(&m_commandPool)));
}

CommandBufferHandle D3D12CommandPool::CreateCommandBuffer(const RHICommandBufferCreateInfo& createInfo)
{
	return nullptr;
}

}