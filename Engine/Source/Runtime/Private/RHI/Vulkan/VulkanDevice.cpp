#include "VulkanDevice.h"

#include "VulkanCommandQueue.h"
#include "VulkanFence.h"
#include "VulkanInstance.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChain.h"

#include <RHI/RHICommandQueue.h>
#include <RHI/RHIFence.h>
#include <RHI/RHIInstance.h>
#include <RHI/RHISemaphore.h>
#include <RHI/RHISwapChain.h>

namespace ow
{

VulkanDevice::VulkanDevice(VkPhysicalDevice physcialDevice, VkDevice device) :
	m_physicalDevice(physcialDevice),
	m_device(device)
{
}

VulkanDevice::~VulkanDevice()
{
	vkDestroyDevice(m_device, nullptr);
}

RHICommandQueue VulkanDevice::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	VkQueue vkCommandQueue;
	vkGetDeviceQueue(m_device, commandQueueCI.ID, 0, &vkCommandQueue);

	auto vulkanCommandQueue = std::make_unique<VulkanCommandQueue>(vkCommandQueue);
	vulkanCommandQueue->SetType(commandQueueCI.Type);

	RHICommandQueue commandQueue;
	commandQueue.Reset(MoveTemp(vulkanCommandQueue));
	return commandQueue;
}

RHIFence VulkanDevice::CreateFence() const
{
	VkFenceCreateInfo fenceCI {};
	fenceCI.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	VkFence vkFence;
	VK_VERIFY(vkCreateFence(m_device, &fenceCI, nullptr, &vkFence));

	auto vulkanFence = std::make_unique<VulkanFence>(m_device, vkFence);

	RHIFence fence;
	fence.Reset(MoveTemp(vulkanFence));
	return fence;
}

RHISemaphore VulkanDevice::CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const
{
	auto vulkanSemaphore = std::make_unique<VulkanSemaphore>();

	RHISemaphore rhiSemaphore;
	rhiSemaphore.Reset(MoveTemp(vulkanSemaphore));
	return rhiSemaphore;
}

RHISwapChain VulkanDevice::CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const
{
	auto vkInstance = static_cast<VkInstance>(createInfo.Instance->GetHandle());

	VkSurfaceKHR vkSurface;
#ifdef PLATFORM_WINDOWS
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = (HWND)createInfo.NativeWindowHandle;
	surfaceCreateInfo.hinstance = (HINSTANCE)createInfo.NativeInstanceHandle;
	VK_VERIFY(vkCreateWin32SurfaceKHR(vkInstance, &surfaceCreateInfo, nullptr, &vkSurface));
#else
	static_assert("Unsupported platform to create surface.");
#endif

	VkBool32 presentSupported;
	VK_VERIFY(vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, 0, vkSurface, &presentSupported));
	assert(presentSupported);

	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	VK_VERIFY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, vkSurface, &surfaceCapabilities));
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
		VK_VERIFY(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, vkSurface, &presentModeCount, nullptr));

		std::vector<VkPresentModeKHR> presentModes(presentModeCount);
		VK_VERIFY(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, vkSurface, &presentModeCount, presentModes.data()));

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

	VkFormat swapChainFormat = ToVK(createInfo.Format);
	VkColorSpaceKHR swapChainColorSpace;
	{
		uint32_t surfaceFormatCount;
		VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, vkSurface, &surfaceFormatCount, nullptr));

		std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
		VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, vkSurface, &surfaceFormatCount, surfaceFormats.data()));

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
	swapChainCreateInfo.surface = vkSurface;
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

	VkSwapchainKHR swapChain;
	VK_VERIFY(vkCreateSwapchainKHR(m_device, &swapChainCreateInfo, nullptr, &swapChain));

	auto vulkanSwapChain = std::make_unique<VulkanSwapChain>(vkInstance, m_device, vkSurface, swapChainFormat, swapChain);
	RHISwapChain rhiSwapChain;
	rhiSwapChain.Reset(MoveTemp(vulkanSwapChain));
	return rhiSwapChain;
}

}