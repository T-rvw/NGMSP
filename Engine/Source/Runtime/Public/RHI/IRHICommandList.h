#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHICommandList : public RefCountObject
{
public:
	virtual ~IRHICommandList() {}
};

}