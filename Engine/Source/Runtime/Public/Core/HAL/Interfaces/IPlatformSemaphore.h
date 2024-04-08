#pragma once

namespace ow
{

class IPlatformSemaphore
{
public:
	virtual void Init(int32 initialCount, int32 maxCount) = 0;
	virtual void Wait() const = 0;
	virtual void Signal(int32 releaseCount) const = 0;
};

}