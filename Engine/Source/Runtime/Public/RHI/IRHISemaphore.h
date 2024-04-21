#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHISemaphore : public RefCountObject
{
public:
	virtual ~IRHISemaphore() {}
};

}