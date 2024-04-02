#pragma once

namespace ow
{

class IRHICommandList
{
public:
	virtual void Init() = 0;
	virtual ~IRHICommandList() {}
};

}