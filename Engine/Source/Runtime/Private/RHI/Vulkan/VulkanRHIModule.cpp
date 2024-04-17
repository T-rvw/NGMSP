#include "VulkanRHIModule.h"

#include "VulkanInstance.h"

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new VulkanRHIModule();
}

VulkanRHIModule::~VulkanRHIModule()
{
	delete this;
}

IRHIInstance* VulkanRHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	return new VulkanInstance(createInfo);
}

IRHIDevice* VulkanRHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	return nullptr;
}

IRHISwapChain* VulkanRHIModule::CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo)
{
	return nullptr;
}

IRHICommandQueue* VulkanRHIModule::CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	return nullptr;
}

IRHIFence* VulkanRHIModule::CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo)
{
	return nullptr;
}

IRHISemaphore* VulkanRHIModule::CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo)
{
	return nullptr;
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