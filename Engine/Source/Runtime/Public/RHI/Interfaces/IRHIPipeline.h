#pragma once

namespace ow
{

class IRHIPipeline
{
public:
	virtual void Init() = 0;
	virtual ~IRHIPipeline() {}
};

}