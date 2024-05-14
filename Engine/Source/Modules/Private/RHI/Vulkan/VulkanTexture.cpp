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
	vkDestroyImage(m_pDevice->GetHandle(), m_image, nullptr);
}

}