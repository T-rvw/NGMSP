#include "VulkanRHIModule.h"

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
	auto& rhiInstance = m_rhiInstances.emplace_back(std::make_unique<VulkanInstance>(createInfo));
	return rhiInstance.get();
}

IRHIDevice* VulkanRHIModule::CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo)
{
	auto vkDevice = static_cast<VulkanAdapter*>(pAdapter)->CreateLogicalDevice(createInfo);
	auto& rhiDevice = m_rhiDevices.emplace_back(std::make_unique<VulkanDevice>(vkDevice));
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