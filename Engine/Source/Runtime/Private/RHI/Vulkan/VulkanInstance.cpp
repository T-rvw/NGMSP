#include <RHI/RHITypes.h>

#include "VulkanInstance.h"

namespace ow
{

void VulkanInstance::Init(const RHIInstanceCreateInfo& createInfo)
{
}

void VulkanInstance::Shutdown()
{
}

int32 VulkanInstance::GetDeviceCount() const
{
	return 1;
}

RHIDevice* VulkanInstance::GetDevice(int32 index)
{
	return nullptr;
}

}