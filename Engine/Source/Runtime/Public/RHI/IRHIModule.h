#pragma once

#include <Core/Modules/IModule.h>

namespace ow
{

class IRHIInstance;

class RHI_API IRHIModule : public IModule
{
public:
	virtual IRHIInstance* CreateRHIInstance() = 0;
};

}