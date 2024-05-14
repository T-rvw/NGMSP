#include "VulkanRHIModule.h"

#include "VulkanInstance.h"

namespace ow
{

C_ABI RHI_API IModule* InitializeModule()
{
	return new VulkanRHIModule();
}

InstanceHandle VulkanRHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanInstance>(createInfo);
}

}