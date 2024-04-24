#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class D3D12RHIModule : public IRHIModule
{
public:
	virtual RefCountPtr<IRHIInstance> CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
};

}