#pragma once

namespace ow
{

class IRHISwapChain
{
public:
	virtual void Init() = 0;
	virtual ~IRHISwapChain() {}
};

}