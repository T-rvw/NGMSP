#include <GPU/Device.h>

#include "DeviceImpl.h"

namespace ow::gpu
{

void Device::Init(const DeviceCreateInfo& createInfo)
{
	return m_pImpl->Init(createInfo);
}

}