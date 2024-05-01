#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHISwapChain : public RefCountObject
{
public:
	virtual ~IRHISwapChain() {}

	uint32 GetCurrentBackBufferIndex() const { return m_currentBackBufferIndex; }

	virtual uint32 GetBackBufferCount() const = 0;
	virtual void AcquireNextTexture(IRHISemaphore* pSemaphore) = 0;
	virtual void Present(IRHISemaphore* pSemaphore) = 0;

protected:
	uint32 m_currentBackBufferIndex = 0;
};

}