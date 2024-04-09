#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHITexture.h>

namespace ow
{

class VulkanTexture : public IRHITexture
{
public:
	VulkanTexture() = default;
	explicit VulkanTexture(VkImage image, VkImageView imageView);
	VulkanTexture(const VulkanTexture&) = delete;
	VulkanTexture& operator=(const VulkanTexture&) = delete;
	VulkanTexture(VulkanTexture&&) = default;
	VulkanTexture& operator=(VulkanTexture&&) = default;
	virtual ~VulkanTexture();

private:
	VkImage m_image = VK_NULL_HANDLE;
	VkImageView m_imageView = VK_NULL_HANDLE;
};

}