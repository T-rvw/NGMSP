#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHISwapChain.h>

namespace ow
{

class VulkanCommandQueue;
class VulkanDevice;

class VulkanSwapChain : public IRHISwapChain
{
public:
	VulkanSwapChain() = delete;
	explicit VulkanSwapChain(const VulkanDevice* pDevice, const RHISwapChainCreateInfo& createInfo);
	VulkanSwapChain(const VulkanSwapChain&) = delete;
	VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
	VulkanSwapChain(VulkanSwapChain&&) = default;
	VulkanSwapChain& operator=(VulkanSwapChain&&) = default;
	virtual ~VulkanSwapChain();

	virtual uint32 GetBackBufferCount() const override;
	virtual void AcquireNextBackBufferTexture(IRHISemaphore* pSemaphore) override;
	virtual void Present(IRHISemaphore* pSemaphore) override;

	VkSwapchainKHR GetHandle() const { return m_swapChain; }
	const VkSwapchainKHR* GetAddressOf() const { return &m_swapChain; }
	VkRenderPass GetRenderPass() const { return m_renderPass; }
	VkFramebuffer GetFrameBuffer(uint32 index) const { return m_framebuffers[index]; }
	VkExtent2D GetSwapChainExtent() const { return m_swapChainExtent; }

private:
	void InitBackBufferImages();
	void InitFramebuffers(const RHISwapChainCreateInfo& createInfo);

private:
	const VulkanDevice* m_pDevice;
	const VulkanCommandQueue* m_pCommandQueue;

	VkSurfaceKHR m_surface;
	VkExtent2D m_swapChainExtent;
	VkSurfaceFormatKHR m_swapChainFormat;
	VkSwapchainKHR m_swapChain;
	Vector<VkFramebuffer> m_framebuffers;
	Vector<VkImage> m_swapChainImages;
	Vector<VkImageView> m_swapChainImageViews;
	
	VkRenderPass m_renderPass;
};

}