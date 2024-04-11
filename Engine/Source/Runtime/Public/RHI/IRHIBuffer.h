#pragma once

namespace ow
{

class IRHIBuffer
{
public:
	virtual ~IRHIBuffer() {}

	virtual void Init() = 0;
};

}