#pragma once

#include <Core/HAL/BasicTypes.h>

namespace ow
{

class IRHIFence
{
public:
	virtual ~IRHIFence() {}

	virtual void Wait(uint64 timeout) = 0;
	virtual void Reset() = 0;
};

}