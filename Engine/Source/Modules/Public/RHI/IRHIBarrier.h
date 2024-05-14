#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIBarrier : public RefCountObject
{
public:
	virtual ~IRHIBarrier() {}
};

}