#include "VulkanRHIModule.h"

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new VulkanRHIModule();
}

void VulkanRHIModule::Shutdown()
{
	delete this;
}

IRHIInstance* VulkanRHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	auto& rhiInstance = m_rhiInstances.emplace_back(std::make_unique<VulkanInstance>(createInfo));
	return rhiInstance.get();
}

IRHIDevice* VulkanRHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	auto* pVulkanAdapter = static_cast<VulkanAdapter*>(pAdapter);
	auto vkDevice = pVulkanAdapter->CreateLogicalDevice(createInfo);
	auto& rhiDevice = m_rhiDevices.emplace_back(std::make_unique<VulkanDevice>(pVulkanAdapter, vkDevice));
	return rhiDevice.get();
}

IRHICommandQueue* VulkanRHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	auto vkCommandQueue = static_cast<VulkanDevice*>(pDevice)->CreateCommandQueue(createInfo);
	auto& rhiCommandQueue = m_rhiCommandQueues.emplace_back(std::make_unique<VulkanCommandQueue>(vkCommandQueue));
	rhiCommandQueue->SetType(createInfo.Type);
	return rhiCommandQueue.get();
}

IRHISwapChain* VulkanRHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	auto* pVulkanDevice = static_cast<VulkanDevice*>(pDevice);
	auto& rhiSwapChain = m_rhiSwapChains.emplace_back(std::make_unique<VulkanSwapChain>(pVulkanDevice, createInfo));
	return rhiSwapChain.get();
}

IRHIFence* VulkanRHIModule::CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo)
{
	auto* pVulkanDevice = static_cast<VulkanDevice*>(pDevice);
	auto& rhiFence = m_rhiFences.emplace_back(std::make_unique<VulkanFence>(pVulkanDevice, createInfo));
	return rhiFence.get();
}

IRHISemaphore* VulkanRHIModule::CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo)
{
	auto vkSemaphore = static_cast<VulkanDevice*>(pDevice)->CreateSemaphore(createInfo);
	auto& rhiSemaphore = m_rhiSemaphores.emplace_back(std::make_unique<VulkanSemaphore>(vkSemaphore));
	return rhiSemaphore.get();
}

IRHIBuffer* VulkanRHIModule::CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo)
{
	return nullptr;
}

IRHISampler* VulkanRHIModule::CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo)
{
	return nullptr;
}

IRHITexture* VulkanRHIModule::CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo)
{
	return nullptr;
}

}