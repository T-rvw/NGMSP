#pragma once

#include <RHI/IRHIModule.h>

namespace ow
{

class IRHIInstance;

class VulkanRHIModule : public IRHIModule
{
public:
	virtual IRHIInstance* CreateRHIInstance() override;
};

}