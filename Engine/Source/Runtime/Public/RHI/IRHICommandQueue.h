#pragma once

#include <Core/Base/RefCountPtr.h>

#include <RHI/RHIEnums.h>

namespace ow
{

class IRHICommandBuffer;
class IRHIFence;
class IRHISemaphore;
class IRHISwapChain;

class IRHICommandQueue : public RefCountObject
{
public:
	virtual ~IRHICommandQueue() {}
	
	virtual void Submit(IRHIFence* pFence) = 0;
	virtual void Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence) = 0;
	virtual void Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence, IRHISemaphore* pWaitSemaphore, IRHISemaphore* pSignalSemaphore) = 0;

	RHICommandType GetType() const { return m_commandQueueType; }

protected:
	void SetType(RHICommandType commandQueueType) { m_commandQueueType = commandQueueType; }
	
protected:
	RHICommandType m_commandQueueType;
};

}