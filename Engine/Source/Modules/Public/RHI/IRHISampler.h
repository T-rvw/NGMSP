#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHISampler : public RefCountObject
{
public:
	virtual ~IRHISampler() {}
};

}