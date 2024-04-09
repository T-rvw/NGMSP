#include "D3D12SwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12SwapChain::D3D12SwapChain(IDXGISwapChain1* pSwapChain) :
	m_swapChain(pSwapChain)
{
}

D3D12SwapChain::~D3D12SwapChain()
{
}

}