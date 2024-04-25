#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHICommandBuffer;
class IRHICommandQueue;
class IRHISemaphore;

class IRHISwapChain : public RefCountObject
{
public:
	virtual ~IRHISwapChain() {}

	virtual uint32 GetCurrentBackBufferIndex() const = 0;
	virtual void AcquireNextBackBufferTexture(IRHISemaphore* pSemaphore) = 0;
	virtual void BeginRenderPass(IRHICommandBuffer* pCommandBuffer) = 0;
	virtual void EndRenderPass(IRHICommandBuffer* pCommandBuffer) = 0;
	virtual void Present(IRHICommandQueue* pCommandQueue, IRHISemaphore* pSemaphore) = 0; 
};

}