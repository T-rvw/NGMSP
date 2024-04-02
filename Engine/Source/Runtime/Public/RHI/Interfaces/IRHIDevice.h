#pragma once

#include <RHI/RHITypes.h>

namespace ow
{

class IRHIDevice
{
public:
	virtual void Init() = 0;
	virtual ~IRHIDevice() {}

	virtual void* GetHandle() const = 0;
};

}