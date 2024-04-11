#pragma once

namespace ow
{

class IRHICommandList
{
public:
	virtual ~IRHICommandList() {}

	virtual void Init() = 0;
};

}