#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

struct RHIDeviceCreateInfo;

class IRHIDevice
{
public:
	virtual void Init(const RHIDeviceCreateInfo& createInfo) = 0;
	virtual void Shutdown() = 0;
};

}