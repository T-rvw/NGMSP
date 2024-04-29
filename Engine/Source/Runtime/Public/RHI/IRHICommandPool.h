#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHICommandPool : public RefCountObject
{
public:
	virtual ~IRHICommandPool() {}

	virtual CommandBufferHandle CreateCommandBuffer(const RHICommandBufferCreateInfo& createInfo) = 0;
};

}