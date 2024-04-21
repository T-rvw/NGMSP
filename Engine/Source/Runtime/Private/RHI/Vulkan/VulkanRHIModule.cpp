#include "VulkanRHIModule.h"

namespace ow
{

C_ABI RHI_API IModule* InitializeModule()
{
	return new VulkanRHIModule();
}

RefCountPtr<IRHIInstance> VulkanRHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanInstance>(createInfo);
}

RefCountPtr<IRHIDevice> VulkanRHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	auto* pVulkanAdapter = static_cast<VulkanAdapter*>(pAdapter);
	auto vkDevice = pVulkanAdapter->CreateLogicalDevice(createInfo);
	return MakeRefCountPtr<VulkanDevice>(pVulkanAdapter, vkDevice);
}

RefCountPtr<IRHICommandQueue> VulkanRHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	auto vkCommandQueue = static_cast<VulkanDevice*>(pDevice)->CreateCommandQueue(createInfo);
	auto rhiCommandQueue = MakeRefCountPtr<VulkanCommandQueue>(vkCommandQueue);
	rhiCommandQueue->SetType(createInfo.Type);
	return rhiCommandQueue;
}

RefCountPtr<IRHISwapChain> VulkanRHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	auto* pVulkanDevice = static_cast<VulkanDevice*>(pDevice);
	return MakeRefCountPtr<VulkanSwapChain>(pVulkanDevice, createInfo);
}

RefCountPtr<IRHIFence> VulkanRHIModule::CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo)
{
	auto* pVulkanDevice = static_cast<VulkanDevice*>(pDevice);
	return MakeRefCountPtr<VulkanFence>(pVulkanDevice, createInfo);
}

RefCountPtr<IRHISemaphore> VulkanRHIModule::CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo)
{
	auto* pVulkanDevice = static_cast<VulkanDevice*>(pDevice);
	return MakeRefCountPtr<VulkanSemaphore>(pVulkanDevice, createInfo);
}

RefCountPtr<IRHIBuffer> VulkanRHIModule::CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanBuffer>();
}

RefCountPtr<IRHISampler> VulkanRHIModule::CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo)
{
	return nullptr;
}

RefCountPtr<IRHITexture> VulkanRHIModule::CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanTexture>();
}

}