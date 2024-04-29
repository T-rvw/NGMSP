#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHITexture.h>

namespace ow
{

class VulkanDevice;

class VulkanTexture : public IRHITexture
{
public:
	VulkanTexture() = default;
	explicit VulkanTexture(const VulkanDevice* pDevice, const RHITextureCreateInfo& createInfo);
	VulkanTexture(const VulkanTexture&) = delete;
	VulkanTexture& operator=(const VulkanTexture&) = delete;
	VulkanTexture(VulkanTexture&&) = default;
	VulkanTexture& operator=(VulkanTexture&&) = default;
	virtual ~VulkanTexture();

private:
	const VulkanDevice* m_pDevice;
	VkImage m_image;
	VkImageView m_imageView;
};

}