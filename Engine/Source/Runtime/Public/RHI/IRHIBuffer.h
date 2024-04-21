#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIBuffer : public RefCountObject
{
public:
	virtual ~IRHIBuffer() {}
};

}