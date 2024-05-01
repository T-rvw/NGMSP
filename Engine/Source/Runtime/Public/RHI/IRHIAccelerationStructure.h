#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIAccelerationStructure : public RefCountObject
{
public:
	virtual ~IRHIAccelerationStructure() {}
};

}