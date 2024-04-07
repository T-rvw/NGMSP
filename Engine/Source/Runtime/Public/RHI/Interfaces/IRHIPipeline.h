#pragma once

namespace ow
{

class IRHIPipeline
{
public:
	virtual ~IRHIPipeline() {}

	virtual void Init() = 0;
};

}