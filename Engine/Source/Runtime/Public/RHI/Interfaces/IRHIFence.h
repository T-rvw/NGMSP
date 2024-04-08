#pragma once

namespace ow
{

class IRHIFence
{
public:
	virtual ~IRHIFence() {}

	virtual void Init() = 0;
};

}