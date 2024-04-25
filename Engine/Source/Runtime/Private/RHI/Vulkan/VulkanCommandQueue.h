#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandQueue.h>

namespace ow
{

class VulkanDevice;

class VulkanCommandQueue : public IRHICommandQueue
{
public:
	VulkanCommandQueue() = default;
	explicit VulkanCommandQueue(const VulkanDevice* pDevice, const RHICommandQueueCreateInfo& createInfo);
	VulkanCommandQueue(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue& operator=(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue(VulkanCommandQueue&&) = default;
	VulkanCommandQueue& operator=(VulkanCommandQueue&&) = default;
	virtual ~VulkanCommandQueue() = default;

	virtual void Submit(IRHIFence* pFence) override;
	virtual void Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence) override;
	virtual void Submit(IRHICommandBuffer* pCommandBuffer, IRHIFence* pFence, IRHISemaphore* pWaitSemaphore, IRHISemaphore* pSignalSemaphore) override;

	VkQueue GetHandle() const { return m_commandQueue; }

private:
	VkQueue m_commandQueue = VK_NULL_HANDLE;
};

}