#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class VulkanRHIModule : public IRHIModule
{
public:
	virtual InstanceHandle CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
};

}