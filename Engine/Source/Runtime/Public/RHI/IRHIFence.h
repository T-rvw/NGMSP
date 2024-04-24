#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIFence : public RefCountObject
{
public:
	virtual ~IRHIFence() {}

	virtual uint64 Signal(uint64 fenceCount) = 0;
	virtual void Wait(uint64 fenceCount) = 0;
	virtual void Wait(uint64 fenceCount, uint64 timeout) = 0;
	virtual bool IsComplete(uint64 fenceCount) = 0;
	virtual void Reset(uint64 fenceCount) = 0;
};

}