#include "VulkanDevice.h"

#include "VulkanCommandQueue.h"

#include <RHI/RHICommandQueue.h>
#include <RHI/RHIDevice.h>

namespace ow
{

VulkanDevice::VulkanDevice(VkDevice device) :
	m_device(device)
{
}

VulkanDevice::~VulkanDevice()
{
	vkDestroyDevice(m_device, nullptr);
}

void VulkanDevice::Init()
{
}

RHICommandQueue VulkanDevice::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	VkQueue vkCommandQueue;
	vkGetDeviceQueue(m_device, commandQueueCI.ID, 0, &vkCommandQueue);

	auto vulkanCommandQueue = std::make_unique<VulkanCommandQueue>(vkCommandQueue);
	vulkanCommandQueue->SetType(commandQueueCI.Type);
	vulkanCommandQueue->Init();

	RHICommandQueue commandQueue;
	commandQueue.Reset(MoveTemp(vulkanCommandQueue));
	return commandQueue;
}

}