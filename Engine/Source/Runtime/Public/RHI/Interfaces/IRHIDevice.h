#pragma once

#include <RHI/RHITypes.h>

namespace ow
{

class RHICommandQueue;
class RHIFence;
class RHISemaphore;

class IRHIDevice
{
public:
	virtual ~IRHIDevice() {}

	virtual void* GetHandle() const = 0;
	virtual RHICommandQueue CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const = 0;
	virtual RHIFence CreateFence() const = 0;
	virtual RHISemaphore CreateSemaphore(const RHISemaphoreCreateInfo& semaphoreCI) const = 0;
};

}