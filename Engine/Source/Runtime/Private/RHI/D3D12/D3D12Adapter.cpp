#include "D3D12Adapter.h"

#include <RHI/RHITypes.h>

namespace ow
{

void D3D12Adapter::Init()
{
}

void D3D12Adapter::SetType(uint32 flags)
{
	auto& info = GetInfo();

	if (flags & DXGI_ADAPTER_FLAG_SOFTWARE)
	{
		info.Type = GPUAdapterType::CPU;
	}
}

}