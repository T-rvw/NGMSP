#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHICommandPool : public RefCountObject
{
public:
	virtual ~IRHICommandPool() {}
};

}