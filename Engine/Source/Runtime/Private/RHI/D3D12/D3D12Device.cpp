#include "D3D12Device.h"

namespace ow
{

D3D12Device::D3D12Device(ID3D12Device* pDevice) :
	m_device(pDevice)
{
}

void D3D12Device::Init()
{
}

bool D3D12Device::CheckFeatrue(RHIFeatrueFlags flags) const
{
	return false;
}

}