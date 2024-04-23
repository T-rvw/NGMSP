#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIBarrier : public RefCountObject
{
public:
	virtual ~IRHIBarrier() {}
};

}