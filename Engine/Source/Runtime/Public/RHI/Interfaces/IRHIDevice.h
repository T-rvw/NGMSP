#pragma once

#include <RHI/RHITypes.h>

namespace ow
{

class RHICommandQueue;

class IRHIDevice
{
public:
	virtual ~IRHIDevice() {}
	
	virtual void Init() = 0;
	virtual void* GetHandle() const = 0;
	virtual RHICommandQueue CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const = 0;
};

}