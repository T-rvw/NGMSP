#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandPool.h>

namespace ow
{

struct RHICommandListCreateInfo;
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

	virtual CommandListHandle CreateCommandList(const RHICommandListCreateInfo& createInfo) override;

	const VulkanDevice* GetDevice() const { return m_pDevice; }
	VkCommandPool GetHandle() const { return m_commandPool; }
	
private:
	const VulkanDevice* m_pDevice;
	VkCommandPool m_commandPool;
};

}