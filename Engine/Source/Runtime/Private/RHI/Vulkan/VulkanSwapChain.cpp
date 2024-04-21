#include "VulkanSwapChain.h"

#include "VulkanDevice.h"
#include "VulkanTexture.h"

#include <RHI/IRHITexture.h>

namespace ow
{

VulkanSwapChain::VulkanSwapChain(const VulkanDevice* pDevice, const RHISwapChainCreateInfo& createInfo) :
    m_pDevice(pDevice)
{
#ifdef VK_USE_PLATFORM_WIN32_KHR
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceCreateInfo.hwnd = (HWND)createInfo.NativeWindowHandle;
    surfaceCreateInfo.hinstance = (HINSTANCE)createInfo.NativeInstanceHandle;
    VK_VERIFY(vkCreateWin32SurfaceKHR(pDevice->GetInstance(), &surfaceCreateInfo, nullptr, &m_surface));
#else
    static_assert("Unsupported platform to create surface.");
#endif

    VkBool32 presentSupported;
    VK_VERIFY(vkGetPhysicalDeviceSurfaceSupportKHR(pDevice->GetAdapter(), 0, m_surface, &presentSupported));
    assert(presentSupported);

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    VK_VERIFY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pDevice->GetAdapter(), m_surface, &surfaceCapabilities));
    assert(createInfo.BackBufferCount >= surfaceCapabilities.minImageCount);
    assert(0 == surfaceCapabilities.maxImageCount || createInfo.BackBufferCount < surfaceCapabilities.maxImageCount);

    VkExtent2D swapChainSize;
    swapChainSize.width = createInfo.BackBufferWidth;
    swapChainSize.height = createInfo.BackBufferHeight;
    const bool supportTransformIdentify = surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    auto surfaceTransformFlags = supportTransformIdentify ? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR : surfaceCapabilities.currentTransform;

    VkPresentModeKHR swapChainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
    if (createInfo.PresentMode != RHIPresentMode::VSync)
    {
        uint32 presentModeCount;
        VK_VERIFY(vkGetPhysicalDeviceSurfacePresentModesKHR(pDevice->GetAdapter(), m_surface, &presentModeCount, nullptr));

        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        VK_VERIFY(vkGetPhysicalDeviceSurfacePresentModesKHR(pDevice->GetAdapter(), m_surface, &presentModeCount, presentModes.data()));

        if (RHIPresentMode::Intermediate == createInfo.PresentMode)
        {
            for (auto presentMode : presentModes)
            {
                if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
                {
                    swapChainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
                    break;
                }
            }
        }
    }

    VkFormat swapChainFormat = VulkanTypes::ToVK(createInfo.Format);
    VkColorSpaceKHR swapChainColorSpace;
    {
        uint32_t surfaceFormatCount;
        VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(pDevice->GetAdapter(), m_surface, &surfaceFormatCount, nullptr));

        std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
        VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(pDevice->GetAdapter(), m_surface, &surfaceFormatCount, surfaceFormats.data()));

        bool findExpectedFormat = false;
        for (const auto& surfaceFormat : surfaceFormats)
        {
            if (swapChainFormat != VK_FORMAT_UNDEFINED &&
                swapChainFormat == surfaceFormat.format)
            {
                findExpectedFormat = true;
                swapChainColorSpace = surfaceFormat.colorSpace;
                break;
            }
        }

        if (!findExpectedFormat)
        {
            swapChainFormat = surfaceFormats.front().format;
            swapChainColorSpace = surfaceFormats.front().colorSpace;
        }
        assert(swapChainFormat != VK_FORMAT_UNDEFINED);
    }

    VkSwapchainCreateInfoKHR swapChainCreateInfo {};
    swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainCreateInfo.surface = m_surface;
    swapChainCreateInfo.minImageCount = createInfo.BackBufferCount;
    swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapChainCreateInfo.preTransform = surfaceTransformFlags;
    swapChainCreateInfo.imageColorSpace = swapChainColorSpace;
    swapChainCreateInfo.imageFormat = swapChainFormat;
    swapChainCreateInfo.pQueueFamilyIndices = nullptr;
    swapChainCreateInfo.queueFamilyIndexCount = 0;
    swapChainCreateInfo.clipped = VK_TRUE;
    swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
    swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapChainCreateInfo.imageExtent = swapChainSize;
    swapChainCreateInfo.imageArrayLayers = 1;
    swapChainCreateInfo.presentMode = swapChainPresentMode;

    VK_VERIFY(vkCreateSwapchainKHR(m_pDevice->GetHandle(), &swapChainCreateInfo, nullptr, &m_swapChain));

    // Create backbuffer views
    uint32 swapChainImageCount;
    VK_VERIFY(vkGetSwapchainImagesKHR(m_pDevice->GetHandle(), m_swapChain, &swapChainImageCount, nullptr));
    assert(swapChainImageCount > 0);

    m_swapChainImages.resize(swapChainImageCount, VK_NULL_HANDLE);
    VK_VERIFY(vkGetSwapchainImagesKHR(m_pDevice->GetHandle(), m_swapChain, &swapChainImageCount, m_swapChainImages.data()));

    m_swapChainImageViews.resize(swapChainImageCount, VK_NULL_HANDLE);
    for (uint32 imageIndex = 0; imageIndex < swapChainImageCount; ++imageIndex)
    {
        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = m_swapChainImages[imageIndex];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = swapChainFormat;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.layerCount = 1;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        VK_VERIFY(vkCreateImageView(m_pDevice->GetHandle(), &imageViewCreateInfo, nullptr, &m_swapChainImageViews[imageIndex]));
    }

    m_format = swapChainFormat;
}

VulkanSwapChain::~VulkanSwapChain()
{
    for (const auto& vkImageView : m_swapChainImageViews)
    {
        vkDestroyImageView(m_pDevice->GetHandle(), vkImageView, nullptr);
    }

	vkDestroySwapchainKHR(m_pDevice->GetHandle(), m_swapChain, nullptr);
    vkDestroySurfaceKHR(m_pDevice->GetInstance(), m_surface, nullptr);
}

}