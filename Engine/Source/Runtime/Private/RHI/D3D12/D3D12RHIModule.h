#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class D3D12RHIModule : public IRHIModule
{
public:
	virtual InstanceHandle CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
};

}