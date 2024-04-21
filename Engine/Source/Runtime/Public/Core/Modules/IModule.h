#pragma once

#include <Core/HAL/APIDefinition.h>
#include <Core/HAL/PlatformModule.h>

namespace ow
{

class CORE_API IModule
{
public:
	virtual ~IModule()
	{
	}
	
	virtual void Init()
	{
	}

	virtual void Shutdown()
	{
	}
};

using InitializeModuleFunc = IModule*(*)(void);

struct ModuleData
{
	InitializeModuleFunc InitFunc = nullptr;
	PlatformModule Library;
};

}