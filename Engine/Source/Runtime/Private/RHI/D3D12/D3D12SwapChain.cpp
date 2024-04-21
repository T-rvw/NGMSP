#include "D3D12SwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12SwapChain::D3D12SwapChain(RefCountPtr<IDXGISwapChain1> pSwapChain) :
	m_swapChain(MoveTemp(pSwapChain))
{
}

D3D12SwapChain::~D3D12SwapChain()
{
}

}