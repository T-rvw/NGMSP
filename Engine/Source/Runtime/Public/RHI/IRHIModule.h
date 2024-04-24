#pragma once

#include <Core/Base/RefCountPtr.h>
#include <Core/Modules/IModule.h>

namespace ow
{

struct RHIInstanceCreateInfo;

class IRHIInstance;

class IRHIModule : public IModule, public RefCountObject
{
public:
	virtual ~IRHIModule() {}

	virtual RefCountPtr<IRHIInstance> CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) = 0;
};

}