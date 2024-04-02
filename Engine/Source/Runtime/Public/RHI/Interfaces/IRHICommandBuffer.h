#pragma once

namespace ow
{

class IRHICommandBuffer
{
public:
	virtual void Init() = 0;
	virtual ~IRHICommandBuffer() {}
};

}