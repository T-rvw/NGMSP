#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHISwapChain.h>

namespace ow
{

class VulkanDevice;

class VulkanSwapChain : public IRHISwapChain
{
public:
	VulkanSwapChain() = default;
	explicit VulkanSwapChain(const VulkanDevice* pDevice, const RHISwapChainCreateInfo& createInfo);
	VulkanSwapChain(const VulkanSwapChain&) = delete;
	VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
	VulkanSwapChain(VulkanSwapChain&&) = default;
	VulkanSwapChain& operator=(VulkanSwapChain&&) = default;
	virtual ~VulkanSwapChain();

private:
	const VulkanDevice* m_pDevice = nullptr;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;
	std::vector<VkImage> m_swapChainImages;
	std::vector<VkImageView> m_swapChainImageViews;
	VkFormat m_format = VK_FORMAT_R8G8B8A8_UNORM;
};

}