#include <GPU/Device.h>

#include "D3D12/DeviceImpl.h"

namespace ow::gpu
{

void Device::Init(const DeviceCreateInfo& createInfo)
{
	return m_pImpl->Init(createInfo);
}

}