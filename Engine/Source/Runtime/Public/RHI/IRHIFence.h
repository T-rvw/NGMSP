#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIFence : public RefCountObject
{
public:
	virtual ~IRHIFence() {}

	virtual void Wait(uint64 timeout) = 0;
	virtual void Reset() = 0;
};

}