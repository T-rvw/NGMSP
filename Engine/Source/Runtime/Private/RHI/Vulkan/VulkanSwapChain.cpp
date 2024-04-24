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
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo {};
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
    m_format = swapChainFormat;

    InitBackBufferImages();
    InitFramebuffers(createInfo);
}

VulkanSwapChain::~VulkanSwapChain()
{
    vkDestroyRenderPass(m_pDevice->GetHandle(), m_renderPass, nullptr);

    for (const auto& framebuffer : m_framebuffers)
    {
        vkDestroyFramebuffer(m_pDevice->GetHandle(), framebuffer, nullptr);
    }

    for (const auto& imageView : m_swapChainImageViews)
    {
        vkDestroyImageView(m_pDevice->GetHandle(), imageView, nullptr);
    }

	vkDestroySwapchainKHR(m_pDevice->GetHandle(), m_swapChain, nullptr);
    vkDestroySurfaceKHR(m_pDevice->GetInstance(), m_surface, nullptr);
}

void VulkanSwapChain::InitBackBufferImages()
{
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
        imageViewCreateInfo.format = m_format;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.layerCount = 1;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        VK_VERIFY(vkCreateImageView(m_pDevice->GetHandle(), &imageViewCreateInfo, nullptr, &m_swapChainImageViews[imageIndex]));
    }
}

void VulkanSwapChain::InitFramebuffers(const RHISwapChainCreateInfo& createInfo)
{
    VkAttachmentDescription attachmentDescription = {};
    attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription.format = m_format;
    attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    VkAttachmentReference attachmentReference = {};
    attachmentReference.attachment = 0;
    attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription = {};
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pColorAttachments = &attachmentReference;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    VkRenderPassCreateInfo renderPassCreateInfo = {};
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.attachmentCount = 1;
    renderPassCreateInfo.subpassCount = 1;
    renderPassCreateInfo.pSubpasses = &subpassDescription;
    renderPassCreateInfo.pAttachments = &attachmentDescription;

    VK_VERIFY(vkCreateRenderPass(m_pDevice->GetHandle(), &renderPassCreateInfo, nullptr, &m_renderPass));

    m_framebuffers.resize(createInfo.BackBufferCount, VK_NULL_HANDLE);
    for (uint32 frameIndex = 0; frameIndex < createInfo.BackBufferCount; ++frameIndex)
    {
        VkFramebufferCreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &m_swapChainImageViews[frameIndex];
        framebufferCreateInfo.width = createInfo.BackBufferWidth;
        framebufferCreateInfo.height = createInfo.BackBufferHeight;
        framebufferCreateInfo.layers = 1;
        framebufferCreateInfo.renderPass = m_renderPass;

        VK_VERIFY(vkCreateFramebuffer(m_pDevice->GetHandle(), &framebufferCreateInfo, nullptr, &m_framebuffers[frameIndex]));
    }
}

}