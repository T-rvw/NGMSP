#include "VulkanDevice.h"

#include "VulkanCommandQueue.h"
#include "VulkanFence.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChain.h"
#include "VulkanSurface.h"

#include <RHI/RHICommandQueue.h>
#include <RHI/RHIFence.h>
#include <RHI/RHISemaphore.h>
#include <RHI/RHISwapChain.h>
#include <RHI/RHISurface.h>

namespace ow
{

VulkanDevice::VulkanDevice(VkPhysicalDevice physcialDevice, VkDevice device) :
	m_physcialDevice(physcialDevice),
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
	vulkanCommandQueue->Init();

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
	VkSurfaceKHR surface = reinterpret_cast<VkSurfaceKHR>(createInfo.Surface->GetHandle());

	VkBool32 presentSupported;
	VK_VERIFY(vkGetPhysicalDeviceSurfaceSupportKHR(m_physcialDevice, 0, surface, &presentSupported));
	assert(presentSupported);

	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	VK_VERIFY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physcialDevice, surface, &surfaceCapabilities));
	assert(createInfo.BackBufferCount >= surfaceCapabilities.minImageCount);
	assert(0 == surfaceCapabilities.maxImageCount || createInfo.BackBufferCount < surfaceCapabilities.maxImageCount);

	VkExtent2D swapChainSize;
	swapChainSize.width = createInfo.Width;
	swapChainSize.height = createInfo.Height;
	const bool supportTransformIdentify = surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	auto surfaceTransformFlags = supportTransformIdentify ? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR : surfaceCapabilities.currentTransform;

	VkPresentModeKHR swapChainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
	if (createInfo.PresentMode != RHIPresentMode::VSync)
	{
		uint32 presentModeCount;
		VK_VERIFY(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physcialDevice, surface, &presentModeCount, nullptr));

		std::vector<VkPresentModeKHR> presentModes(presentModeCount);
		VK_VERIFY(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physcialDevice, surface, &presentModeCount, presentModes.data()));

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

	VkFormat surfaceFormat;
	VkColorSpaceKHR swapChainColorSpace;
	{
		uint32_t surfaceFormatCount;
		VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physcialDevice, surface, &surfaceFormatCount, nullptr));

		std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
		VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physcialDevice, surface, &surfaceFormatCount, surfaceFormats.data()));

		if (1 == surfaceFormatCount && VK_FORMAT_UNDEFINED == surfaceFormats.front().format)
		{
			surfaceFormat = VK_FORMAT_R8G8B8A8_UNORM;
		}
		else
		{
			surfaceFormat = surfaceFormats.front().format;
		}

		swapChainColorSpace = surfaceFormats.front().colorSpace;
	}

	VkSwapchainCreateInfoKHR swapChainCreateInfo {};
	swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainCreateInfo.surface = surface;
	swapChainCreateInfo.minImageCount = createInfo.BackBufferCount;
	swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapChainCreateInfo.preTransform = surfaceTransformFlags;
	swapChainCreateInfo.imageColorSpace = swapChainColorSpace;
	swapChainCreateInfo.imageFormat = surfaceFormat;
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

	auto vulkanSwapChain = std::make_unique<VulkanSwapChain>(m_device, swapChain);
	vulkanSwapChain->SetImageFormat(surfaceFormat);

	RHISwapChain rhiSwapChain;
	rhiSwapChain.Reset(MoveTemp(vulkanSwapChain));
	return rhiSwapChain;
}

}