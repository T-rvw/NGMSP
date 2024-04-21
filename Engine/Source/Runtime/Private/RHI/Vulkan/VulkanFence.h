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

	virtual uint64 Signal(uint64 fenceValue) override;
	virtual void Wait(uint64 fenceValue) override;
	virtual bool IsComplete(uint64 fenceValue) override;
	virtual void Reset() override;

private:
	const VulkanDevice* m_pDevice = nullptr;
	VkFence m_fence = VK_NULL_HANDLE;
};

}