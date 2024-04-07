#pragma once

namespace ow
{

class IRHISwapChain
{
public:
	virtual ~IRHISwapChain() {}
	
	virtual void Init() = 0;
};

}