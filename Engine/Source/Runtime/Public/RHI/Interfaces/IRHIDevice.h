#pragma once

#include <RHI/RHITypes.h>

namespace ow
{

class IRHIDevice
{
public:
	virtual void Init() = 0;

	virtual void* GetHandle() const = 0;

	virtual bool CheckFeatrue(RHIFeatrueFlags flags) const = 0;
};

}