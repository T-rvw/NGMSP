#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIFence : public RefCountObject
{
public:
	virtual ~IRHIFence() {}

	virtual uint64 Signal(uint64 fenceValue) = 0;
	virtual void Wait(uint64 fenceValue) = 0;
	virtual bool IsComplete(uint64 fenceValue) = 0;
	virtual void Reset() = 0;
};

}