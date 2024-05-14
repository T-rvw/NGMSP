#include "VulkanPipelineLayout.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanPipelineLayout::VulkanPipelineLayout(const VulkanDevice* pDevice, const RHIPipelineLayoutCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkPipelineLayoutCreateInfo layoutCI = {};
	layoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	VK_VERIFY(vkCreatePipelineLayout(m_pDevice->GetHandle(), &layoutCI, nullptr, &m_pipelineLayout));
}

VulkanPipelineLayout::~VulkanPipelineLayout()
{
	vkDestroyPipelineLayout(m_pDevice->GetHandle(), m_pipelineLayout, nullptr);
}

}