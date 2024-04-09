#include "VulkanSwapChain.h"

#include "VulkanTexture.h"

#include <RHI/RHITexture.h>
#include <RHI/RHITypes.h>

namespace ow
{

VulkanSwapChain::VulkanSwapChain(VkInstance instance, VkDevice device, VkSurfaceKHR surface, VkFormat format, VkSwapchainKHR swapChain) :
	m_instance(instance),
	m_device(device),
	m_surface(surface),
    m_format(format),
	m_swapChain(swapChain)
{
    uint32 swapChainImageCount;
    VK_VERIFY(vkGetSwapchainImagesKHR(m_device, m_swapChain, &swapChainImageCount, nullptr));
    assert(swapChainImageCount > 0);

    m_swapChainImages.resize(swapChainImageCount, VK_NULL_HANDLE);
    VK_VERIFY(vkGetSwapchainImagesKHR(m_device, m_swapChain, &swapChainImageCount, m_swapChainImages.data()));

    m_swapChainImageViews.resize(swapChainImageCount, VK_NULL_HANDLE);
    for (uint32 imageIndex = 0; imageIndex < swapChainImageCount; ++imageIndex)
    {
        VkImageViewCreateInfo imageViewCreateInfo {};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = m_swapChainImages[imageIndex];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = m_format;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.layerCount = 1;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        VK_VERIFY(vkCreateImageView(m_device, &imageViewCreateInfo, nullptr, &m_swapChainImageViews[imageIndex]));
    }
}

VulkanSwapChain::~VulkanSwapChain()
{
    for (const auto& vkImageView : m_swapChainImageViews)
    {
        vkDestroyImageView(m_device, vkImageView, nullptr);
    }

	vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

}