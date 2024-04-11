#pragma once

namespace ow
{

class IRHISemaphore
{
public:
	virtual ~IRHISemaphore() {}

	virtual void Init() = 0;
};

}