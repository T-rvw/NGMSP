#pragma once

#include "VulkanAdapter.h"
#include "VulkanBuffer.h"
#include "VulkanCommandQueue.h"
#include "VulkanDevice.h"
#include "VulkanFence.h"
#include "VulkanInstance.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChain.h"
#include "VulkanTexture.h"

#include <RHI/IRHIModule.h>

#include <list>
#include <memory>

namespace ow
{

class VulkanRHIModule : public IRHIModule
{
public:
	virtual ~VulkanRHIModule();

	virtual IRHIInstance* CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
	virtual IRHIDevice* CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) override;

	virtual IRHICommandQueue* CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) override;
	virtual IRHISwapChain* CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) override;

	virtual IRHIFence* CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) override;
	virtual IRHISemaphore* CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) override;

	virtual IRHIBuffer* CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) override;
	virtual IRHISampler* CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) override;
	virtual IRHITexture* CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) override;

private:
	std::list<std::unique_ptr<VulkanInstance>> m_rhiInstances;
	std::list<std::unique_ptr<VulkanDevice>> m_rhiDevices;
	std::list<std::unique_ptr<VulkanCommandQueue>> m_rhiCommandQueues;
	std::list<std::unique_ptr<VulkanSwapChain>> m_rhiSwapChains;
	std::list<std::unique_ptr<VulkanFence>> m_rhiFences;
	std::list<std::unique_ptr<VulkanSemaphore>> m_rhiSemaphores;
	std::list<std::unique_ptr<VulkanBuffer>> m_rhiBuffer;
	std::list<std::unique_ptr<VulkanTexture>> m_rhiTextures;
};

}