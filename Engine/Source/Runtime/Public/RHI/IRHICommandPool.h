#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

struct RHICommandBufferCreateInfo;

class IRHICommandBuffer;

class IRHICommandPool : public RefCountObject
{
public:
	virtual ~IRHICommandPool() {}

	virtual RefCountPtr<IRHICommandBuffer> CreateCommandBuffer(const RHICommandBufferCreateInfo& createInfo) = 0;
};

}