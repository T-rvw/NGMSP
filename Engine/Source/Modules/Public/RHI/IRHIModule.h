#pragma once

#include <Core/Modules/IModule.h>
#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIModule : public IModule, public RefCountObject
{
public:
	virtual ~IRHIModule() {}

	virtual InstanceHandle CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) = 0;
};

}