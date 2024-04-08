#pragma once

namespace ow
{

class IRHIBarrier
{
public:
	virtual ~IRHIBarrier() {}

	virtual void Init() = 0;
};

}