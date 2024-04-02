#pragma once

namespace ow
{

class IRHICommandPool
{
public:
	virtual void Init() = 0;
	virtual ~IRHICommandPool() {}
};

}