#include "VulkanTexture.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanTexture::VulkanTexture(VkImage image, VkImageView imageView) :
	m_image(image),
	m_imageView(imageView)
{
}

VulkanTexture::~VulkanTexture()
{
}

}