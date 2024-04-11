#include "VulkanRHIModule.h"

#include <Core/HAL/APIDefinition.h>

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new VulkanRHIModule();
}

IRHIInstance* VulkanRHIModule::CreateRHIInstance()
{
	return nullptr;
}

}