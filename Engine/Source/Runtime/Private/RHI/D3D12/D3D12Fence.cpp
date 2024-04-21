#include "D3D12Fence.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Fence::D3D12Fence(RefCountPtr<ID3D12Fence> pFence) :
	m_fence(MoveTemp(pFence))
{
}

D3D12Fence::~D3D12Fence()
{
}

void D3D12Fence::Wait(uint64 timeout)
{

}

void D3D12Fence::Reset()
{

}

}