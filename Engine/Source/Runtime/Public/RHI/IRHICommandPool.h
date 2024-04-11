#pragma once

namespace ow
{

class IRHICommandPool
{
public:
	virtual ~IRHICommandPool() {}
	
	virtual void Init() = 0;
};

}