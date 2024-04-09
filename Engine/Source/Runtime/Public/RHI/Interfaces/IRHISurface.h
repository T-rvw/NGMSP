#pragma once

namespace ow
{

class IRHISurface
{
public:
	virtual ~IRHISurface() {}

	virtual void* GetHandle() const = 0;
};

}