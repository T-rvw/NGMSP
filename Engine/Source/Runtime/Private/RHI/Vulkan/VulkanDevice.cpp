#include "VulkanDevice.h"

#include "VulkanCommandQueue.h"
#include "VulkanFence.h"

#include <RHI/RHICommandQueue.h>
#include <RHI/RHIFence.h>

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

RHIFence VulkanDevice::CreateFence() const
{
	VkFenceCreateInfo fenceCI {};
	fenceCI.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	VkFence vkFence;
	VK_VERIFY(vkCreateFence(m_device, &fenceCI, nullptr, &vkFence));

	auto vulkanFence = std::make_unique<VulkanFence>(vkFence);
	vulkanFence->Init();

	RHIFence fence;
	fence.Reset(MoveTemp(vulkanFence));
	return fence;
}

}