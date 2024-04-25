#include "VulkanTexture.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanTexture::VulkanTexture(const VulkanDevice* pDevice, const RHITextureCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
}

VulkanTexture::~VulkanTexture()
{
	vkDestroyImageView(m_pDevice->GetHandle(), m_imageView, nullptr);
	vkDestroyImage(m_pDevice->GetHandle(), m_image, nullptr);
}

}