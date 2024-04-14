#include "VulkanRHIModule.h"

#include "VulkanInstance.h"

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new VulkanRHIModule();
}

IRHIInstance* VulkanRHIModule::CreateRHIInstance()
{
	return new VulkanInstance();
}

}