#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class RHIDevice;
struct RHIInstanceCreateInfo;

class IRHIInstance
{
public:
	virtual void Init(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual void Shutdown() = 0;

	virtual int32 GetDeviceCount() const = 0;
	virtual RHIDevice* GetDevice(int32 index) = 0;
};

}