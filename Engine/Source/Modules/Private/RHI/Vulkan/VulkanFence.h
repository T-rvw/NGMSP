#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIFence.h>

namespace ow
{

class VulkanDevice;

class VulkanFence : public IRHIFence
{
public:
	VulkanFence() = delete;
	explicit VulkanFence(const VulkanDevice* pDevice, const RHIFenceCreateInfo& createInfo);
	VulkanFence(const VulkanFence&) = delete;
	VulkanFence& operator=(const VulkanFence&) = delete;
	VulkanFence(VulkanFence&&) = default;
	VulkanFence& operator=(VulkanFence&&) = default;
	virtual ~VulkanFence();

	virtual uint64 Signal(uint64 fenceCount) override;
	virtual void Wait(uint64 fenceCount) override;
	virtual void Wait(uint64 fenceCount, uint64 timeout) override;
	virtual bool IsComplete(uint64 fenceCount) override;
	virtual void Reset(uint64 fenceCount) override;

	VkFence GetHandle() const { return m_fence; }

private:
	const VulkanDevice* m_pDevice;
	VkFence m_fence;
};

}