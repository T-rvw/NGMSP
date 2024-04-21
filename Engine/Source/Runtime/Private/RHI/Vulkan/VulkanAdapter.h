#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIAdapter.h>

namespace ow
{

struct VulkanAdapterFeatures
{
	VulkanAdapterFeatures()
	{
		Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		Features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
		Features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
		Features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;

		Features.pNext = &Features11;
		Features11.pNext = &Features12;
		Features12.pNext = &Features13;
		pNextChain = &Features13;
	}

	VkPhysicalDeviceFeatures2 Features {};
	VkPhysicalDeviceVulkan11Features Features11 {};
	VkPhysicalDeviceVulkan12Features Features12 {};
	VkPhysicalDeviceVulkan13Features Features13 {};
	void* pNextChain;
};

struct VulkanAdapterProperties
{
	VulkanAdapterProperties()
	{
		Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		Properties11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
		Properties12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
		Properties13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
	
		Properties.pNext = &Properties11;
		Properties11.pNext = &Properties12;
		Properties12.pNext = &Properties13;
		pNextChain = Properties13.pNext;
	}

	VkPhysicalDeviceProperties2 Properties {};
	VkPhysicalDeviceVulkan11Properties Properties11 {};
	VkPhysicalDeviceVulkan12Properties Properties12 {};
	VkPhysicalDeviceVulkan13Properties Properties13 {};
	void* pNextChain;
};

class VulkanInstance;

class VulkanAdapter : public IRHIAdapter
{
public:
	VulkanAdapter() = delete;
	explicit VulkanAdapter(const VulkanInstance* pInstance, VkPhysicalDevice physcialDevice);
	VulkanAdapter(const VulkanAdapter&) = delete;
	VulkanAdapter& operator=(const VulkanAdapter&) = delete;
	VulkanAdapter(VulkanAdapter&&) = default;
	VulkanAdapter& operator=(VulkanAdapter&&) = default;
	virtual ~VulkanAdapter();

	virtual void Init() override;
	virtual void EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos) override;
	virtual void EnumerateCommandQueues(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs) override;

	VkPhysicalDevice GetHandle() const { return m_physicalDevice; }
	VkInstance GetInstance() const;

private:
	friend class VulkanRHIModule;
	void InitOutputInfos();
	void InitCommandQueueCreateInfos();
	VkDevice CreateLogicalDevice(const RHIDeviceCreateInfo& deviceCI);

private:
	const VulkanInstance* m_pInstance = nullptr;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	std::vector<VkExtensionProperties> m_availableExtensions;
	std::unique_ptr<VulkanAdapterFeatures> m_adapterFeatures;
	std::unique_ptr<VulkanAdapterProperties> m_adapterProperties;
	std::vector<RHIOutputInfo> m_outputInfos;
	std::vector<RHICommandQueueCreateInfo> m_commandQueueCIs;
};

}