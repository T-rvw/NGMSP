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

	virtual void Wait(uint64 timeout) override;
	virtual void Reset() override;

private:
	const VulkanDevice* m_pDevice = nullptr;
	VkFence m_fence = VK_NULL_HANDLE;
};

}