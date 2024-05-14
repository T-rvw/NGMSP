#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHISemaphore : public RefCountObject
{
public:
	virtual ~IRHISemaphore() {}
};

}