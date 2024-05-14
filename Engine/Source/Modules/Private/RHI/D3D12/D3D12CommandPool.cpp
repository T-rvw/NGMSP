#include "D3D12CommandPool.h"

#include "D3D12CommandList.h"
#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12CommandPool::D3D12CommandPool(const D3D12Device* pDevice, const RHICommandPoolCreateInfo& createInfo) :
	m_pDevice(pDevice),
	m_commandType(D3D12Types::ToD3D12(createInfo.Type))
{
	D3D12_VERIFY(pDevice->GetHandle()->CreateCommandAllocator(m_commandType, IID_PPV_ARGS(&m_commandPool)));
}

CommandListHandle D3D12CommandPool::CreateCommandList(const RHICommandListCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12CommandList>(this, createInfo);
}

}