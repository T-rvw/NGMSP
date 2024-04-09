#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHISwapChain.h>

namespace ow
{

class VulkanSwapChain : public IRHISwapChain
{
public:
	VulkanSwapChain() = default;
	explicit VulkanSwapChain(VkDevice device, VkSwapchainKHR swapChain);
	VulkanSwapChain(const VulkanSwapChain&) = delete;
	VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
	VulkanSwapChain(VulkanSwapChain&&) = default;
	VulkanSwapChain& operator=(VulkanSwapChain&&) = default;
	virtual ~VulkanSwapChain();

	virtual std::vector<RHITexture> GetBackBufferTextures() const override;

	void SetImageFormat(VkFormat imageFormat) { m_imageFormat = imageFormat; }

private:
	VkDevice m_device = VK_NULL_HANDLE;
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;
	VkFormat m_imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
};

}