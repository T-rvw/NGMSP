#include <RHI/RHITypes.h>

#include "D3D12Instance.h"

namespace ow
{

void D3D12Instance::Init(const RHIInstanceCreateInfo& createInfo)
{
}

void D3D12Instance::Shutdown()
{
}

int32 D3D12Instance::GetDeviceCount() const
{
	return 1;
}

RHIDevice* D3D12Instance::GetDevice(int32 index)
{
	return nullptr;
}

}