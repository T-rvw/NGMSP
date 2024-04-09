#pragma once

#include <vector>

namespace ow
{

class RHITexture;

class IRHISwapChain
{
public:
	virtual ~IRHISwapChain() {}

	virtual std::vector<RHITexture> GetBackBufferTextures() const = 0;
};

}