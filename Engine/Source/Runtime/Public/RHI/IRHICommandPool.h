#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHICommandPool : public RefCountObject
{
public:
	virtual ~IRHICommandPool() {}

	virtual CommandListHandle CreateCommandList(const RHICommandListCreateInfo& createInfo) = 0;
};

}