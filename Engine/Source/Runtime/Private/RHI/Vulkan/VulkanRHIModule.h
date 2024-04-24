#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class VulkanRHIModule : public IRHIModule
{
public:
	virtual RefCountPtr<IRHIInstance> CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
};

}