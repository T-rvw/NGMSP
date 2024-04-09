#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHISwapChain.h>

namespace ow
{

class VulkanSwapChain : public IRHISwapChain
{
public:
	VulkanSwapChain() = default;
	explicit VulkanSwapChain(VkSwapchainKHR swapChain);
	VulkanSwapChain(const VulkanSwapChain&) = delete;
	VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
	VulkanSwapChain(VulkanSwapChain&&) = default;
	VulkanSwapChain& operator=(VulkanSwapChain&&) = default;
	virtual ~VulkanSwapChain();

private:
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;
};

}