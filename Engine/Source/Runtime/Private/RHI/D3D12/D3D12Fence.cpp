#include "D3D12Fence.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Fence::D3D12Fence(ID3D12Fence* pFence) :
	m_fence(pFence)
{
}

D3D12Fence::~D3D12Fence()
{
}

void D3D12Fence::Init()
{
}

}