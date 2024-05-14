#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIPipelineLayout.h>

namespace ow
{

class VulkanDevice;

class VulkanPipelineLayout : public IRHIPipelineLayout
{
public:
	VulkanPipelineLayout() = delete;
	VulkanPipelineLayout(const VulkanDevice* pDevice, const RHIPipelineLayoutCreateInfo& createInfo);
	VulkanPipelineLayout(const VulkanPipelineLayout&) = delete;
	VulkanPipelineLayout& operator=(const VulkanPipelineLayout&) = delete;
	VulkanPipelineLayout(VulkanPipelineLayout&&) = default;
	VulkanPipelineLayout& operator=(VulkanPipelineLayout&&) = default;
	virtual ~VulkanPipelineLayout();

	VkPipelineLayout GetHandle() const { return m_pipelineLayout; }

private:
	const VulkanDevice* m_pDevice;
	VkPipelineLayout m_pipelineLayout;
};

}