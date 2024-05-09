#include "VulkanAdapter.h"

#include "VulkanDevice.h"
#include "VulkanInstance.h"

#include <unordered_set>

namespace ow
{

VulkanAdapter::VulkanAdapter(const VulkanInstance* m_pInstance, VkPhysicalDevice physicalDevice) :
	m_pInstance(m_pInstance),
	m_physicalDevice(physicalDevice)
{
	VkPhysicalDeviceProperties properties = {};
	vkGetPhysicalDeviceProperties(physicalDevice, &properties);

	m_info.Type = VulkanTypes::ToRHI(properties.deviceType);
	m_info.Name = properties.deviceName;
	m_info.Vendor = GetGPUVendor(properties.vendorID);
	m_info.DeviceID = properties.deviceID;

	VkPhysicalDeviceMemoryProperties memoryProperties = {};
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

	const bool isIntegratedGPU = GPUAdapterType::Integrated == m_info.Type;
	uint64 videoMemorySize = 0;
	uint64 systemMemorySize = 0;
	Vector<Vector<const VkMemoryType*>> memoryHeapTypes(memoryProperties.memoryHeapCount);
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
			systemMemorySize += memoryHeap.size;
		}
	}

	m_info.VideoMemorySize = videoMemorySize;
	m_info.SystemMemorySize = systemMemorySize;

	uint32 extensionCount;
	VK_VERIFY(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, nullptr));
	m_availableExtensions.resize(extensionCount);
	VK_VERIFY(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, m_availableExtensions.data()));

	m_adapterFeatures = std::make_unique<VulkanAdapterFeatures>();
	m_adapterProperties = std::make_unique<VulkanAdapterProperties>();

	InitOutputInfos();
	InitCommandQueueCreateInfos();
}

VulkanAdapter::~VulkanAdapter()
{
}

VkInstance VulkanAdapter::GetInstance() const
{
	return m_pInstance->GetHandle();
}

void VulkanAdapter::InitOutputInfos()
{
	if (!VulkanUtils::FindExtension(m_pInstance->GetAvaialableExtensions(), VK_KHR_DISPLAY_EXTENSION_NAME))
	{
		printf("[Warning] Failed to query output infos.\n");
		return;
	}

	uint32 displayCount;
	VK_VERIFY(vkGetPhysicalDeviceDisplayPropertiesKHR(m_physicalDevice, &displayCount, nullptr));
	Vector<VkDisplayPropertiesKHR> adapterDisplayInfos(displayCount);
	VK_VERIFY(vkGetPhysicalDeviceDisplayPropertiesKHR(m_physicalDevice, &displayCount, adapterDisplayInfos.data()));
	
	for (uint32 displayIndex = 0; displayIndex < displayCount; ++displayIndex)
	{
		VkDisplayPropertiesKHR vkDisplay = adapterDisplayInfos[displayIndex];
	
		auto& outputInfo = m_outputInfos.emplace_back();
		outputInfo.Name = vkDisplay.displayName;
	
		uint32_t modeCount;
		VK_VERIFY(vkGetDisplayModePropertiesKHR(m_physicalDevice, vkDisplay.display, &modeCount, nullptr));
		Vector<VkDisplayModePropertiesKHR> adapterDisplayModeInfos(modeCount);
		VK_VERIFY(vkGetDisplayModePropertiesKHR(m_physicalDevice, vkDisplay.display, &modeCount, adapterDisplayModeInfos.data()));
	
		for (uint32 modeIndex = 0; modeIndex < modeCount; ++modeIndex)
		{
			VkDisplayModePropertiesKHR vkDisplayMode = adapterDisplayModeInfos[modeIndex];
	
		}
	}
}

void VulkanAdapter::InitCommandQueueCreateInfos()
{
	uint32 queueFamilyCount;
	Vector<VkQueueFamilyProperties2> adapterQueueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties2(m_physicalDevice, &queueFamilyCount, nullptr);
	adapterQueueFamilies.resize(queueFamilyCount, { VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
	vkGetPhysicalDeviceQueueFamilyProperties2(m_physicalDevice, &queueFamilyCount, adapterQueueFamilies.data());

	Vector<RHICommandQueueCreateInfo> commandQueueCIs;
	for (uint32 queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount; ++queueFamilyIndex)
	{
		const auto& queueFamily = adapterQueueFamilies[queueFamilyIndex];
		const auto& queueFamilyProperties = queueFamily.queueFamilyProperties;
		if (0 == queueFamilyProperties.queueCount)
		{
			continue;
		}

		uint32 rhiQueueStartIndex = static_cast<uint32>(commandQueueCIs.size());
		uint32 rhiQueueEndIndex = rhiQueueStartIndex;
		bool supportGraphics = queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
		bool supportCompute = queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT;
		bool supportTransfer = queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT;
		bool supportVideoDecode = queueFamilyProperties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR;
		if (supportGraphics)
		{
			auto& createInfo = commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::Graphics;
			createInfo.FamilyIndex = queueFamilyIndex;
			createInfo.Priority += supportCompute ? -0.1f : 0.0f;
			createInfo.Priority += supportTransfer ? -0.1f : 0.0f;
			createInfo.Priority += supportVideoDecode ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		if (supportCompute)
		{
			auto& createInfo = commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::Compute;
			createInfo.FamilyIndex = queueFamilyIndex;
			createInfo.Priority += supportGraphics ? -0.1f : 0.0f;
			createInfo.Priority += supportTransfer ? -0.1f : 0.0f;
			createInfo.Priority += supportVideoDecode ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		if (supportTransfer)
		{
			auto& createInfo = commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::Copy;
			createInfo.FamilyIndex = queueFamilyIndex;
			createInfo.Priority += supportGraphics ? -0.1f : 0.0f;
			createInfo.Priority += supportCompute ? -0.1f : 0.0f;
			createInfo.Priority += supportVideoDecode ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		if (supportVideoDecode)
		{
			auto& createInfo = commandQueueCIs.emplace_back();
			createInfo.Type = RHICommandType::VideoDecode;
			createInfo.FamilyIndex = queueFamilyIndex;
			createInfo.Priority += supportGraphics ? -0.1f : 0.0f;
			createInfo.Priority += supportCompute ? -0.1f : 0.0f;
			createInfo.Priority += supportTransfer ? -0.1f : 0.0f;
			++rhiQueueEndIndex;
		}

		uint32 rhiQueueCount = rhiQueueEndIndex - rhiQueueStartIndex;
		for (uint32 queueIndex = rhiQueueStartIndex; queueIndex < rhiQueueEndIndex; ++queueIndex)
		{
			commandQueueCIs[queueIndex].IsDedicated = rhiQueueCount == 1;
		}
	}

	FindSuitableCommandQueues(MoveTemp(commandQueueCIs));
}

void VulkanAdapter::EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos)
{
	if (!pOutputInfos)
	{
		outputCount = static_cast<uint32>(m_outputInfos.size());
		return;
	}

	for (uint32 outputIndex = 0; outputIndex < outputCount; ++outputIndex)
	{
		pOutputInfos[outputIndex] = &m_outputInfos[outputIndex];
	}
}

DeviceHandle VulkanAdapter::CreateDevice(const RHIDeviceCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanDevice>(this, createInfo);
}

Optional<int32> VulkanAdapter::FindSuitableCommandQueue(RHICommandType commandType, const Vector<RHICommandQueueCreateInfo>& createInfos)
{
	Optional<int32> bestCIIndex;
	float bestScore = -1.0f;
	for (int32 ciIndex = 0, ciCount = static_cast<int32>(createInfos.size()); ciIndex < ciCount; ++ciIndex)
	{
		const auto& createInfo = createInfos[ciIndex];
		if (commandType == createInfo.Type)
		{
			float score = 0.0f;
			if (createInfo.IsDedicated)
			{
				score += 1U << 31;
			}
			score += createInfo.Priority;

			if (score > bestScore)
			{
				bestCIIndex = ciIndex;
				bestScore = score;
			}
		}
	}

	return bestCIIndex;
}

void VulkanAdapter::FindSuitableCommandQueues(Vector<RHICommandQueueCreateInfo>&& createInfos)
{
	std::unordered_set<int32> queueIndexes;

	constexpr uint32 typeCount = EnumCount<RHICommandType>();
	for (uint32 typeIndex = 0; typeIndex < typeCount; ++typeIndex)
	{
		auto commandType = static_cast<RHICommandType>(typeIndex);
		if (auto optIndex = FindSuitableCommandQueue(commandType, createInfos); optIndex.has_value())
		{
			queueIndexes.insert(optIndex.value());
		}
	}

	for (auto queueIndex : queueIndexes)
	{
		uint32 tyoeIndex = static_cast<uint32>(createInfos[queueIndex].Type);
		m_commandQueueCIs[tyoeIndex] = createInfos[queueIndex];
	}
}

}