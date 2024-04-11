#pragma once

namespace ow
{

class IRHICommandQueue;
class IRHIFence;
class IRHISemaphore;
class IRHISwapChain;

struct RHICommandQueueCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHISwapChainCreateInfo;

class IRHIDevice
{
public:
	virtual ~IRHIDevice() {}

	virtual void* GetHandle() const = 0;
	virtual IRHICommandQueue* CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const = 0;
	virtual IRHIFence* CreateFence() const = 0;
	virtual IRHISemaphore* CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const = 0;
	virtual IRHISwapChain* CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const = 0;
};

}