#include "D3D12CommandQueue.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12CommandQueue::D3D12CommandQueue(RefCountPtr<ID3D12CommandQueue> pCommandQueue) :
	m_commandQueue(MoveTemp(pCommandQueue))
{
}

}