#pragma once

namespace ow
{

class IRHIBuffer
{
public:
	virtual void Init() = 0;
	virtual ~IRHIBuffer() {}
};

}