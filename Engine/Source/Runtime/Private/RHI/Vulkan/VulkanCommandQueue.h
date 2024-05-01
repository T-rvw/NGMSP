#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandQueue.h>

namespace ow
{

class VulkanDevice;

class VulkanCommandQueue : public IRHICommandQueue
{
public:
	VulkanCommandQueue() = delete;
	explicit VulkanCommandQueue(const VulkanDevice* pDevice, const RHICommandQueueCreateInfo& createInfo);
	VulkanCommandQueue(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue& operator=(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue(VulkanCommandQueue&&) = default;
	VulkanCommandQueue& operator=(VulkanCommandQueue&&) = default;
	virtual ~VulkanCommandQueue() = default;

	virtual void Submit(IRHIFence* pFence) override;
	virtual void Submit(IRHICommandList* pCommandBuffer, IRHIFence* pFence) override;
	virtual void Submit(IRHICommandList* pCommandBuffer, IRHIFence* pFence, IRHISemaphore* pWaitSemaphore, IRHISemaphore* pSignalSemaphore) override;

	VkQueue GetHandle() const { return m_commandQueue; }
	uint32 GetFamilyIndex() const { return m_familyIndex; }

private:
	VkQueue m_commandQueue;
	uint32 m_familyIndex;
};

}