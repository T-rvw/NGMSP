#pragma once

namespace ow
{

class IRHITexture
{
public:
	virtual ~IRHITexture() {}

	virtual void Init() = 0;
};

}