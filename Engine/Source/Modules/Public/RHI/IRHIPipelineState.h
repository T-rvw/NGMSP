#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIPipelineState : public RefCountObject
{
public:
	virtual ~IRHIPipelineState() {}
};

}