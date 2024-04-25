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

	virtual uint32 GetCurrentBackBufferIndex() const override;
	virtual void AcquireNextBackBufferTexture(IRHISemaphore* pSemaphore) override;
	virtual void BeginRenderPass(IRHICommandBuffer* pCommandBuffer) override;
	virtual void EndRenderPass(IRHICommandBuffer* pCommandBuffer) override;
	virtual void Present(IRHICommandQueue* pCommandQueue, IRHISemaphore* pSemaphore) override;

	VkSwapchainKHR GetHandle() const { return m_swapChain; }
	const VkSwapchainKHR* GetAddressOf() const { return &m_swapChain; }

private:
	void InitBackBufferImages();
	void InitFramebuffers(const RHISwapChainCreateInfo& createInfo);

private:
	const VulkanDevice* m_pDevice = nullptr;

	uint32 m_currentBackBufferIndex = 0;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	VkExtent2D m_swapChainExtent;
	VkSurfaceFormatKHR m_swapChainFormat;
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;
	std::vector<VkFramebuffer> m_framebuffers;
	std::vector<VkImage> m_swapChainImages;
	std::vector<VkImageView> m_swapChainImageViews;
	
	VkRenderPass m_renderPass = VK_NULL_HANDLE;
};

}