#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandPool.h>

namespace ow
{

struct RHICommandBufferCreateInfo;
struct RHICommandPoolCreateInfo;

class VulkanDevice;

class VulkanCommandPool : public IRHICommandPool
{
public:
	VulkanCommandPool() = delete;
	explicit VulkanCommandPool(const VulkanDevice* pDevice, const RHICommandPoolCreateInfo& createInfo);
	VulkanCommandPool(const VulkanCommandPool&) = delete;
	VulkanCommandPool& operator=(const VulkanCommandPool&) = delete;
	VulkanCommandPool(VulkanCommandPool&&) = default;
	VulkanCommandPool& operator=(VulkanCommandPool&&) = default;
	virtual ~VulkanCommandPool();

	VkCommandPool GetHandle() const { return m_commandPool; }
	VkCommandBuffer CreateCommandBuffer(const RHICommandBufferCreateInfo& createInfo);

private:
	const VulkanDevice* m_pDevice = nullptr;
	VkCommandPool m_commandPool = VK_NULL_HANDLE;
};

}