#pragma once

#include "VulkanHeader.h"

#include <Core/Base/Optional.h>
#include <Core/Base/UniquePtr.h>
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

	VkPhysicalDeviceFeatures2 Features = {};
	VkPhysicalDeviceVulkan11Features Features11 = {};
	VkPhysicalDeviceVulkan12Features Features12 = {};
	VkPhysicalDeviceVulkan13Features Features13 = {};
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

	VkPhysicalDeviceProperties2 Properties = {};
	VkPhysicalDeviceVulkan11Properties Properties11 = {};
	VkPhysicalDeviceVulkan12Properties Properties12 = {};
	VkPhysicalDeviceVulkan13Properties Properties13 = {};
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

	virtual void EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos) override;
	virtual DeviceHandle CreateDevice(const RHIDeviceCreateInfo& createInfo) override;

	VkPhysicalDevice GetHandle() const { return m_physicalDevice; }
	VkInstance GetInstance() const;

	const RHICommandQueueCreateInfo& GetCommandQueueCreateInfo(RHICommandType commandType) const { return m_commandQueueCIs[static_cast<uint32>(commandType)]; }
	const Vector<VkExtensionProperties>& GetAvailableExtensions() const { return m_availableExtensions; }
	VulkanAdapterFeatures* GetFeatures() const { return m_adapterFeatures.Get(); }
	VulkanAdapterProperties* GetProperties() const { return m_adapterProperties.Get(); }

private:
	void InitOutputInfos();
	void InitCommandQueueCreateInfos();
	Optional<int32> FindSuitableCommandQueue(RHICommandType commandType, const Vector<RHICommandQueueCreateInfo>& createInfos);
	void FindSuitableCommandQueues(Vector<RHICommandQueueCreateInfo>&& createInfos);

private:
	const VulkanInstance* m_pInstance;

	VkPhysicalDevice m_physicalDevice;
	Vector<VkExtensionProperties> m_availableExtensions;
	UniquePtr<VulkanAdapterFeatures> m_adapterFeatures;
	UniquePtr<VulkanAdapterProperties> m_adapterProperties;
	Vector<RHIOutputInfo> m_outputInfos;
	RHICommandQueueCreateInfo m_commandQueueCIs[EnumCount<RHICommandType>()];
};

}