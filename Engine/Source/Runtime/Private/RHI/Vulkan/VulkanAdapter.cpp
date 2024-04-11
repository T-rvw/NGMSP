#include "VulkanAdapter.h"

#include "VulkanDevice.h"

#include <RHI//IRHIAdapter.h>
#include <RHI/IRHIDevice.h>

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

VulkanAdapter::VulkanAdapter(VkPhysicalDevice physicalDevice) :
	m_physicalDevice(physicalDevice)
{
	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(physicalDevice, &properties);

	SetType(properties.deviceType);
	m_info.Name = properties.deviceName;
	m_info.Vendor = GetGPUVendor(properties.vendorID);
	m_info.DeviceID = properties.deviceID;

	VkPhysicalDeviceMemoryProperties memoryProperties{};
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

	const bool isIntegratedGPU = GPUAdapterType::Integrated == m_info.Type;
	uint64 videoMemorySize = 0;
	uint64 systemMemorySize = 0;
	uint64 sharedMemorySize = 0;
	std::vector<std::vector<const VkMemoryType*>> memoryHeapTypes(memoryProperties.memoryHeapCount);
	for (uint32 memoryTypeIndex = 0; memoryTypeIndex < memoryProperties.memoryTypeCount; ++memoryTypeIndex)
	{
		const VkMemoryType& memoryType = memoryProperties.memoryTypes[memoryTypeIndex];
		assert(memoryType.heapIndex < memoryProperties.memoryHeapCount);
		memoryHeapTypes[memoryType.heapIndex].push_back(&memoryType);
	}

	for (uint32 memoryHeapIndex = 0; memoryHeapIndex < memoryProperties.memoryHeapCount; ++memoryHeapIndex)
	{
		const VkMemoryHeap& memoryHeap = memoryProperties.memoryHeaps[memoryHeapIndex];
		bool isHeapInLocalDevice = (memoryHeap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) > 0;

		if (isHeapInLocalDevice)
		{
			videoMemorySize += memoryHeap.size;
		}
		else
		{
			sharedMemorySize += memoryHeap.size;
		}
	}

	m_info.VideoMemorySize = videoMemorySize;
	m_info.SystemMemorySize = systemMemorySize;
	m_info.SharedMemorySize = sharedMemorySize;
}

VulkanAdapter::~VulkanAdapter()
{
}

void VulkanAdapter::Init()
{
	uint32 extensionCount;
	VK_VERIFY(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, nullptr));
	m_adapterExtensions.resize(extensionCount);
	VK_VERIFY(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, m_adapterExtensions.data()));

	m_adapterFeatures = std::make_unique<VulkanAdapterFeatures>();
	m_adapterProperties = std::make_unique<VulkanAdapterProperties>();
	
	InitCommandQueueCreateInfos();
}

void VulkanAdapter::InitCommandQueueCreateInfos()
{
	uint32 queueFamilyCount;
	std::vector<VkQueueFamilyProperties2> adapterQueueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties2(m_physicalDevice, &queueFamilyCount, nullptr);
	adapterQueueFamilies.resize(queueFamilyCount, { VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
	vkGetPhysicalDeviceQueueFamilyProperties2(m_physicalDevice, &queueFamilyCount, adapterQueueFamilies.data());

	for (uint32 queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount; ++queueFamilyIndex)
	{
		const auto& queueFamily = adapterQueueFamilies[queueFamilyIndex];
		const auto& queueFamilyProperties = queueFamily.queueFamilyProperties;
		if (0 == queueFamilyProperties.queueCount)
		{
			continue;
		}

		uint32 rhiQueueStartIndex = static_cast<uint32>(m_commandQueueCIs.size());
		uint32 rhiQueueEndIndex = rhiQueueStartIndex;
		bool supportGraphics = queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
		bool supportCompute = queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT;
		bool supportTransfer = queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT;
		bool supportVideoDecode = queueFamilyProperties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR;
		if (supportGraphics)
		{
			auto& createInfo = m_commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::Graphics;
			createInfo.ID = queueFamilyIndex;
			createInfo.Priority += supportCompute ? -0.1f : 0.0f;
			createInfo.Priority += supportTransfer ? -0.1f : 0.0f;
			createInfo.Priority += supportVideoDecode ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		if (supportCompute)
		{
			auto& createInfo = m_commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::Compute;
			createInfo.ID = queueFamilyIndex;
			createInfo.Priority += supportGraphics ? -0.1f : 0.0f;
			createInfo.Priority += supportTransfer ? -0.1f : 0.0f;
			createInfo.Priority += supportVideoDecode ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		if (supportTransfer)
		{
			auto& createInfo = m_commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::Copy;
			createInfo.ID = queueFamilyIndex;
			createInfo.Priority += supportGraphics ? -0.1f : 0.0f;
			createInfo.Priority += supportCompute ? -0.1f : 0.0f;
			createInfo.Priority += supportVideoDecode ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		if (supportVideoDecode)
		{
			auto& createInfo = m_commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::VideoDecode;
			createInfo.ID = queueFamilyIndex;
			createInfo.Priority += supportGraphics ? -0.1f : 0.0f;
			createInfo.Priority += supportCompute ? -0.1f : 0.0f;
			createInfo.Priority += supportTransfer ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		uint32 rhiQueueCount = rhiQueueEndIndex - rhiQueueStartIndex;
		for (uint32 queueIndex = rhiQueueStartIndex; queueIndex < rhiQueueEndIndex; ++queueIndex)
		{
			m_commandQueueCIs[queueIndex].IsDedicated = rhiQueueCount == 1;
		}
	}
}

void VulkanAdapter::QueryCommandQueueCreateInfos(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs)
{
	if (nullptr == pCommandQueueCIs)
	{
		queueCICount = static_cast<uint32>(m_commandQueueCIs.size());
		return;
	}

	for (uint32 queueIndex = 0; queueIndex < queueCICount; ++queueIndex)
	{
		pCommandQueueCIs[queueIndex] = &m_commandQueueCIs[queueIndex];
	}
}

IRHIDevice* VulkanAdapter::CreateDevice(const RHIDeviceCreateInfo& deviceCI, uint32 queueCICount, const RHICommandQueueCreateInfo** pCommandQueueCIs) const
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

		vkGetPhysicalDeviceFeatures2(m_physicalDevice, &m_adapterFeatures->Features);
		vkGetPhysicalDeviceProperties2(m_physicalDevice, &m_adapterProperties->Properties);
	}

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	for (uint32 queueCIIndex = 0; queueCIIndex < queueCICount; ++queueCIIndex)
	{
		const RHICommandQueueCreateInfo* commandQueueCI = pCommandQueueCIs[queueCIIndex];

		VkDeviceQueueCreateInfo& queueCreateInfo = queueCreateInfos.emplace_back();
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = commandQueueCI->ID;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &commandQueueCI->Priority;
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
	VK_VERIFY(vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &vkDevice));
	assert(vkDevice != VK_NULL_HANDLE);
	volkLoadDevice(vkDevice);

	auto vulkanDevice = std::make_unique<VulkanDevice>(m_physicalDevice, vkDevice);

	return nullptr;
}

void VulkanAdapter::SetType(VkPhysicalDeviceType deviceType)
{
	switch (deviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
	{
		m_info.Type = GPUAdapterType::Discrete;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
	{
		m_info.Type = GPUAdapterType::Integrated;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
	{
		m_info.Type = GPUAdapterType::Virtual;
		break;
	}
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
	{
		m_info.Type = GPUAdapterType::CPU;
		break;
	}
	default:
	{
		m_info.Type = GPUAdapterType::CPU;
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