#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIAdapter.h>

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

class RHIDevice;

class VulkanAdapter : public IRHIAdapter
{
public:
	VulkanAdapter() = default;
	explicit VulkanAdapter(VkPhysicalDevice physcialDevice);
	VulkanAdapter(const VulkanAdapter&) = delete;
	VulkanAdapter& operator=(const VulkanAdapter&) = delete;
	VulkanAdapter(VulkanAdapter&&) = default;
	VulkanAdapter& operator=(VulkanAdapter&&) = default;
	virtual ~VulkanAdapter();

	virtual void Init() override;
	virtual void* GetHandle() const override { return m_physcialDevice; }

	GPUAdapterType GetType() const;
	void SetType(VkPhysicalDeviceType deviceType);

	bool CheckExtensionSupport(const char* pExtensionName) const;
	bool EnableExtensionSafely(std::vector<const char*>& extensions, const char* pExtensionName) const;
	bool EnableExtensionsSafely(std::vector<const char*>& extensions, const std::vector<const char*>& requireExtensions) const;

	RHIDevice CreateDevice(const RHIDeviceCreateInfo& createInfo) const;

private:
	VkPhysicalDevice m_physcialDevice = VK_NULL_HANDLE;
	std::vector<VkExtensionProperties> m_adapterExtensions;
	std::unique_ptr<VulkanAdapterFeatures> m_adapterFeatures;
	std::unique_ptr<VulkanAdapterProperties> m_adapterProperties;
	std::vector<VkQueueFamilyProperties2> m_adapterQueueFamilies;
};

}