#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHICommandBuffer : public RefCountObject
{
public:
	virtual ~IRHICommandBuffer() {}
};

}