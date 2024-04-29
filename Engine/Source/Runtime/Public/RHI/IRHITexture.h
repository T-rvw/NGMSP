#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHITexture : public RefCountObject
{
public:
	virtual ~IRHITexture() {}
};

}