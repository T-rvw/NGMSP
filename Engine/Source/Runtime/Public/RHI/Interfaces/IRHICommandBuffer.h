#pragma once

namespace ow
{

class IRHICommandBuffer
{
public:
	virtual ~IRHICommandBuffer() {}

	virtual void Init() = 0;
};

}