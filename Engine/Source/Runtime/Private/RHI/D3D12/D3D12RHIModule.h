#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class IRHIInstance;

class D3D12RHIModule : public IRHIModule
{
public:
	virtual IRHIInstance* CreateRHIInstance() override;
};

}