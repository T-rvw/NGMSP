#include "VulkanSwapChain.h"

#include "VulkanTexture.h"

#include <RHI/RHITexture.h>
#include <RHI/RHITypes.h>

namespace ow
{

VulkanSwapChain::VulkanSwapChain(VkDevice device, VkSwapchainKHR swapChain) :
	m_device(device),
	m_swapChain(swapChain)
{
}

VulkanSwapChain::~VulkanSwapChain()
{
	vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
}

std::vector<RHITexture> VulkanSwapChain::GetBackBufferTextures() const
{
    std::vector<RHITexture> rhiTextures;

	uint32 swapChainImageCount;
	VK_VERIFY(vkGetSwapchainImagesKHR(m_device, m_swapChain, &swapChainImageCount, nullptr));
	assert(swapChainImageCount > 0);

	std::vector<VkImage> swapChainImages(swapChainImageCount);
	VK_VERIFY(vkGetSwapchainImagesKHR(m_device, m_swapChain, &swapChainImageCount, swapChainImages.data()));

    std::vector<VkImageView> swapChainImageViews(swapChainImageCount);
    for (uint32 imageIndex = 0; imageIndex < swapChainImageCount; ++imageIndex)
    {
        VkImageViewCreateInfo imageViewCreateInfo = {};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = swapChainImages[imageIndex];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = m_imageFormat;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.layerCount = 1;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        VK_VERIFY(vkCreateImageView(m_device, &imageViewCreateInfo, nullptr, &swapChainImageViews[imageIndex]));

        auto vulkanTexture = std::make_unique<VulkanTexture>(swapChainImages[imageIndex], swapChainImageViews[imageIndex]);

        auto& rhiTexture = rhiTextures.emplace_back();
        rhiTexture.Reset(MoveTemp(vulkanTexture));
    }

    return rhiTextures;
}

}