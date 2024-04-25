#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

#ifdef CreateSemaphore
#undef CreateSemaphore
#endif

struct RHIBarrierCreateInfo;
struct RHIBufferCreateInfo;
struct RHICommandPoolCreateInfo;
struct RHICommandQueueCreateInfo;
struct RHIFenceCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHIShaderCreateInfo;
struct RHISwapChainCreateInfo;
struct RHITextureCreateInfo;

class IRHIBarrier;
class IRHIBuffer;
class IRHICommandPool;
class IRHICommandQueue;
class IRHIFence;
class IRHISemaphore;
class IRHIShader;
class IRHISwapChain;
class IRHITexture;

class IRHIDevice : public RefCountObject
{
public:
	virtual ~IRHIDevice() {}

	virtual RefCountPtr<IRHISwapChain> CreateSwapChain(const RHISwapChainCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHICommandPool> CreateCommandPool(const RHICommandPoolCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHICommandQueue> CreateCommandQueue(const RHICommandQueueCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHIBarrier> CreateBarrier(const RHIBarrierCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHIFence> CreateFence(const RHIFenceCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHISemaphore> CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHIBuffer> CreateBuffer(const RHIBufferCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHITexture> CreateTexture(const RHITextureCreateInfo& createInfo) = 0;
};

}