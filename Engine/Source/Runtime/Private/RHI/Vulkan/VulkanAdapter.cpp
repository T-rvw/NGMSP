#include "VulkanAdapter.h"

#include "VulkanDevice.h"

#include <RHI/RHIDevice.h>

namespace
{

struct VulkanAdapterRayTracing
{
	VulkanAdapterRayTracing()
	{
		ExtensionNames =
		{
			VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
			VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME, // required by VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME
			VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
			VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME, // required by VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME
			VK_KHR_RAY_QUERY_EXTENSION_NAME
		};

		AccelerateStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
		RayTracingPipelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
		RayQueryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
		AccelerateStructureFeatures.pNext = &RayTracingPipelineFeatures;
		RayTracingPipelineFeatures.pNext = &RayQueryFeatures;

		AccelerateStructureProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
		RayTracingPipelineProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
		AccelerateStructureProperties.pNext = &RayTracingPipelineProperties;
	}

	void AppendFeatures(void** pNextChain)
	{
		*pNextChain = &RayQueryFeatures;
		pNextChain = &RayQueryFeatures.pNext;
	}

	void AppendProperties(void** pNextChain)
	{
		*pNextChain = &RayTracingPipelineProperties;
		pNextChain = &RayTracingPipelineProperties.pNext;
	}

	std::vector<const char*> ExtensionNames;

	VkPhysicalDeviceAccelerationStructureFeaturesKHR AccelerateStructureFeatures {};
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR RayTracingPipelineFeatures {};
	VkPhysicalDeviceRayQueryFeaturesKHR RayQueryFeatures {};

	VkPhysicalDeviceAccelerationStructurePropertiesKHR AccelerateStructureProperties {};
	VkPhysicalDeviceRayTracingPipelinePropertiesKHR RayTracingPipelineProperties {};
};

struct VulkanAdapterMeshShader
{
	VulkanAdapterMeshShader()
	{
		ExtensionNames =
		{
			VK_EXT_MESH_SHADER_EXTENSION_NAME
		};

		MeshShaderFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;

		MeshShaderProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
	}

	void AppendFeatures(void** pNextChain)
	{
		*pNextChain = &MeshShaderFeatures;
		pNextChain = &MeshShaderFeatures.pNext;
	}

	void AppendProperties(void** pNextChain)
	{
		*pNextChain = &MeshShaderProperties;
		pNextChain = &MeshShaderProperties.pNext;
	}

	std::vector<const char*> ExtensionNames;

	VkPhysicalDeviceMeshShaderFeaturesEXT MeshShaderFeatures {};

	VkPhysicalDeviceMeshShaderPropertiesEXT MeshShaderProperties {};
};

}

namespace ow
{

VulkanAdapter::VulkanAdapter(VkPhysicalDevice physcialDevice) :
	m_physcialDevice(physcialDevice)
{
}

VulkanAdapter::~VulkanAdapter() = default;

void VulkanAdapter::Init()
{
	uint32 extensionCount;
	VK_VERIFY(vkEnumerateDeviceExtensionProperties(m_physcialDevice, nullptr, &extensionCount, nullptr));
	m_adapterExtensions.resize(extensionCount);
	VK_VERIFY(vkEnumerateDeviceExtensionProperties(m_physcialDevice, nullptr, &extensionCount, m_adapterExtensions.data()));

	m_adapterFeatures = std::make_unique<VulkanAdapterFeatures>();
	m_adapterProperties = std::make_unique<VulkanAdapterProperties>();
	
	uint32 queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties2(m_physcialDevice, &queueFamilyCount, nullptr);
	m_adapterQueueFamilies.resize(queueFamilyCount, { VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
	vkGetPhysicalDeviceQueueFamilyProperties2(m_physcialDevice, &queueFamilyCount, m_adapterQueueFamilies.data());
}

std::vector<RHICommandQueueCreateInfo> VulkanAdapter::QueryCommandQueueCreateInfos()
{
	std::vector<RHICommandQueueCreateInfo> rhiQueueCreateInfos;
	uint32 queueFamilyCount = static_cast<uint32>(m_adapterQueueFamilies.size());
	for (uint32 queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount; ++queueFamilyIndex)
	{
		const auto& queueFamily = m_adapterQueueFamilies[queueFamilyIndex];
		const auto& queueFamilyProperties = queueFamily.queueFamilyProperties;
		if (0 == queueFamilyProperties.queueCount)
		{
			continue;
		}

		uint32 rhiQueueStartIndex = static_cast<uint32>(rhiQueueCreateInfos.size());
		uint32 rhiQueueEndIndex = rhiQueueStartIndex;
		bool supportGraphics = queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
		bool supportCompute = queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT;
		bool supportTransfer = queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT;
		bool supportVideoDecode = queueFamilyProperties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR;
		if (supportGraphics)
		{
			auto& commandQueue = rhiQueueCreateInfos.emplace_back();
			commandQueue.Type = RHICommandQueueType::Graphics;
			commandQueue.ID = queueFamilyIndex;
			++rhiQueueEndIndex;
		}

		if (supportCompute)
		{
			auto& commandQueue = rhiQueueCreateInfos.emplace_back();
			commandQueue.Type = RHICommandQueueType::Compute;
			commandQueue.ID = queueFamilyIndex;
			++rhiQueueEndIndex;
		}

		if (supportTransfer)
		{
			auto& commandQueue = rhiQueueCreateInfos.emplace_back();
			commandQueue.Type = RHICommandQueueType::Copy;
			commandQueue.ID = queueFamilyIndex;
			++rhiQueueEndIndex;
		}

		if (supportVideoDecode)
		{
			auto& commandQueue = rhiQueueCreateInfos.emplace_back();
			commandQueue.Type = RHICommandQueueType::VideoDecode;
			commandQueue.ID = queueFamilyIndex;
			++rhiQueueEndIndex;
		}

		uint32 rhiQueueCount = rhiQueueEndIndex - rhiQueueStartIndex;
		for (uint32 queueIndex = rhiQueueStartIndex; queueIndex < rhiQueueEndIndex; ++queueIndex)
		{
			rhiQueueCreateInfos[queueIndex].IsDedicated = rhiQueueCount == 1;
		}
	}

	return rhiQueueCreateInfos;
}

RHIDevice VulkanAdapter::CreateDevice(const RHIDeviceCreateInfo& deviceCI, const std::vector<RHICommandQueueCreateInfo>& commandQueueCIs) const
{
	// Enable extra extensions/features/properties by requirement.
	std::vector<const char*> enabledExtensions;
	{
		void** pFeaturesNextChain = &m_adapterFeatures->pNextChain;
		void** pPropertiesNextChain = &m_adapterProperties->pNextChain;

		const RHIFeatures& requiredFeatrues = deviceCI.Features;
		if (!requiredFeatrues.Headless)
		{
			assert(EnableExtensionSafely(enabledExtensions, VK_KHR_SWAPCHAIN_EXTENSION_NAME));
		}

		VulkanAdapterRayTracing rayTracing;
		if (requiredFeatrues.RayTracing &&
			EnableExtensionsSafely(enabledExtensions, rayTracing.ExtensionNames))
		{
			rayTracing.AppendFeatures(pFeaturesNextChain);
			rayTracing.AppendProperties(pPropertiesNextChain);
		}

		VulkanAdapterMeshShader meshShader;
		if (requiredFeatrues.MeshShaders &&
			EnableExtensionsSafely(enabledExtensions, meshShader.ExtensionNames))
		{
			meshShader.AppendFeatures(pFeaturesNextChain);
			meshShader.AppendProperties(pPropertiesNextChain);
		}

		vkGetPhysicalDeviceFeatures2(m_physcialDevice, &m_adapterFeatures->Features);
		vkGetPhysicalDeviceProperties2(m_physcialDevice, &m_adapterProperties->Properties);
	}

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	for (const auto& commandQueueCI : commandQueueCIs)
	{
		VkDeviceQueueCreateInfo& queueCreateInfo = queueCreateInfos.emplace_back();
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = commandQueueCI.ID;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &commandQueueCI.Priority;
	}

	VkDeviceCreateInfo deviceCreateInfo {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32>(queueCreateInfos.size());
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
	deviceCreateInfo.pEnabledFeatures = nullptr;
	deviceCreateInfo.pNext = &m_adapterFeatures->Features;
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32>(enabledExtensions.size());
	deviceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();

	VkDevice vkDevice;
	VK_VERIFY(vkCreateDevice(m_physcialDevice, &deviceCreateInfo, nullptr, &vkDevice));
	assert(vkDevice != VK_NULL_HANDLE);
	volkLoadDevice(vkDevice);

	auto vulkanDevice = std::make_unique<VulkanDevice>(vkDevice);

	RHIDevice device;
	device.Reset(MoveTemp(vulkanDevice));
	return device;
}

GPUAdapterType VulkanAdapter::GetType() const
{
	return GetInfo().Type;
}

void VulkanAdapter::SetType(VkPhysicalDeviceType deviceType)
{
	auto& info = GetInfo();

	switch (deviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
	{
		info.Type = GPUAdapterType::Discrete;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
	{
		info.Type = GPUAdapterType::Integrated;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
	{
		info.Type = GPUAdapterType::Virtual;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
	{
		info.Type = GPUAdapterType::CPU;
		break;
	}
	default:
	{
		info.Type = GPUAdapterType::CPU;
		break;
	}
	}
}

bool VulkanAdapter::CheckExtensionSupport(const char* pExtensionName) const
{
	for (const auto& extension : m_adapterExtensions)
	{
		if (0 == strcmp(extension.extensionName, pExtensionName))
		{
			return true;
		}
	}

	return false;
}

bool VulkanAdapter::EnableExtensionSafely(std::vector<const char*>& extensions, const char* pExtensionName) const
{
	if (!CheckExtensionSupport(pExtensionName))
	{
		return false;
	}

	extensions.push_back(pExtensionName);
	return true;
}

bool VulkanAdapter::EnableExtensionsSafely(std::vector<const char*>& extensions, const std::vector<const char*>& requireExtensions) const
{
	for (const auto& requireExtension : requireExtensions)
	{
		if (!CheckExtensionSupport(requireExtension))
		{
			return false;
		}
	}

	for (const auto& requireExtension : requireExtensions)
	{
		extensions.push_back(requireExtension);
	}

	return true;
}

}