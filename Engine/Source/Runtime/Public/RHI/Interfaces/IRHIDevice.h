#pragma once

namespace ow
{

class IRHIDevice
{
public:
	virtual void Init() = 0;

	virtual void* GetHandle() const = 0;
};

}