#pragma once

#include "VulkanHeader.h"

#include <RHI/IRHIShader.h>

namespace ow
{

class VulkanDevice;

class VulkanShader : public IRHIShader
{
public:
	VulkanShader() = delete;
	VulkanShader(const VulkanDevice* pDevice, const RHIShaderCreateInfo& createInfo);
	VulkanShader(const VulkanShader&) = delete;
	VulkanShader& operator=(const VulkanShader&) = delete;
	VulkanShader(VulkanShader&&) = default;
	VulkanShader& operator=(VulkanShader&&) = default;
	virtual ~VulkanShader();

	VkShaderModule GetHandle() const { return m_shaderModule; }

private:
	const VulkanDevice* m_pDevice;
	VkShaderModule m_shaderModule;
};

}