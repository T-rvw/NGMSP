#include "VulkanShader.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanShader::VulkanShader(const VulkanDevice* pDevice, const RHIShaderCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
    VkShaderModuleCreateInfo shaderCI = {};
    shaderCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

    VK_VERIFY(vkCreateShaderModule(m_pDevice->GetHandle(), &shaderCI, nullptr, &m_shaderModule));
}

VulkanShader::~VulkanShader()
{
    vkDestroyShaderModule(m_pDevice->GetHandle(), m_shaderModule, nullptr);
}

}