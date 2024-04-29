#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIShader : public RefCountObject
{
public:
	virtual ~IRHIShader() {}
};

}