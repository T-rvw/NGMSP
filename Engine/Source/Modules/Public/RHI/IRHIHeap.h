#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIHeap : public RefCountObject
{
public:
	virtual ~IRHIHeap() {}
};

}