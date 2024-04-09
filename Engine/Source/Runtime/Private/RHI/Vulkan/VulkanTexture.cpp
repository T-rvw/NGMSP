#include "VulkanTexture.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanTexture::VulkanTexture(VkDevice device, VkImage image, VkImageView imageView) :
	m_device(device),
	m_image(image),
	m_imageView(imageView)
{
}

VulkanTexture::~VulkanTexture()
{
	vkDestroyImageView(m_device, m_imageView, nullptr);
	//vkDestroyImage(m_device, m_image, nullptr);
}

}