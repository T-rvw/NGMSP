#include "VulkanInstance.h"

#include "VulkanAdapter.h"

#include <RHI/RHIAdapter.h>
#include <RHI/RHITypes.h>

namespace ow
{

VulkanInstance::~VulkanInstance()
{
	if (m_instance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_instance, nullptr);
		m_instance = VK_NULL_HANDLE;
	}
}

void VulkanInstance::Init(const RHIInstanceCreateInfo& createInfo)
{
	assert(VK_NULL_HANDLE == m_instance);

	std::vector<const char*> instanceExtensions =
	{
		"VK_KHR_surface", "VK_KHR_win32_surface",
	};
	if (createInfo.EnableDebugLayer)
	{
		instanceExtensions.push_back("VK_EXT_debug_report");
	}

	std::vector<const char*> instanceLayers;
	if (createInfo.EnableGPUValidator)
	{
		//instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
	}

	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion = VK_API_VERSION_1_0;
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pApplicationName = "AMD Vulkan Sample application";
	applicationInfo.pEngineName = "AMD Vulkan Sample Engine";

	VkInstanceCreateInfo instanceCreateInfo {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
	instanceCreateInfo.enabledLayerCount = static_cast<uint32_t> (instanceLayers.size());
	instanceCreateInfo.pApplicationInfo = &applicationInfo;

	VK_VERITY(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));
	assert(m_instance != VK_NULL_HANDLE);
}

std::vector<std::unique_ptr<RHIAdapter>> VulkanInstance::EnumAdapters()
{
	uint32 physicalDeviceCount = 0;
	VK_VERITY(vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	VK_VERITY(vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, physicalDevices.data()));

	std::vector<std::unique_ptr<RHIAdapter>> adapters;
	for (const auto physicalDevice : physicalDevices)
	{
		VkPhysicalDeviceProperties properties {};
		vkGetPhysicalDeviceProperties(physicalDevice, &properties);
		
		VkPhysicalDeviceMemoryProperties memoryProperties {};
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

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

			bool isTypeHostVisible = false;
			for (const auto* memoryType : memoryHeapTypes[memoryHeapIndex])
			{
				isTypeHostVisible |= (memoryType->propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) > 0;
			}

			if (isHeapInLocalDevice)
			{
				if (isTypeHostVisible)
				{
					sharedMemorySize += memoryHeap.size;
				}
				else
				{
					videoMemorySize += memoryHeap.size;
				}
			}
			else
			{
				systemMemorySize += memoryHeap.size;
			}
		}

		auto vkAdapter = std::make_unique<VulkanAdapter>(physicalDevice);
		vkAdapter->SetName(properties.deviceName);
		vkAdapter->SetType(properties.deviceType);
		vkAdapter->SetVendor(properties.vendorID);
		vkAdapter->SetVideoMemorySize(videoMemorySize);
		vkAdapter->SetSystemMemorySize(systemMemorySize);
		vkAdapter->SetSharedMemorySize(sharedMemorySize);

		auto& pAdapter = adapters.emplace_back(std::make_unique<RHIAdapter>());
		pAdapter->Init(MoveTemp(vkAdapter));
	}

	return adapters;
}

//void VulkanInstance::InitDevices(const RHIInstanceCreateInfo& createInfo)
//{
//	uint32 physicalDeviceCount = 0;
//	vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
//
//	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
//	vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, physicalDevices.data());
//
//	VkPhysicalDevice selectPhysicalDevice = VK_NULL_HANDLE;
//	int32 graphicsQueueIndex = -1;
//	for (auto physicalDevice : physicalDevices)
//	{
//		uint32 queueFamilyPropertyCount = 0;
//		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, nullptr);
//
//		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
//		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());
//
//		for (int32 propertyIndex = 0; propertyIndex < queueFamilyProperties.size(); ++propertyIndex)
//		{
//			const auto& queueFamilyProperty = queueFamilyProperties[propertyIndex];
//			if (queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT)
//			{
//				selectPhysicalDevice = physicalDevice;
//				graphicsQueueIndex = propertyIndex;
//				break;
//			}
//		}
//	}
//
//	VkDeviceQueueCreateInfo deviceQueueCreateInfo {};
//	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//	deviceQueueCreateInfo.queueCount = 1;
//	deviceQueueCreateInfo.queueFamilyIndex = graphicsQueueIndex;
//
//	std::vector<const char*> deviceLayers =
//	{
//		//"VK_LAYER_LUNARG_standard_validation"
//	};
//
//	VkPhysicalDeviceFeatures enabledFeatures = {};
//	enabledFeatures.shaderClipDistance = true;
//
//	VkDeviceCreateInfo deviceCreateInfo = {};
//	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//	deviceCreateInfo.queueCreateInfoCount = 1;
//	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
//	deviceCreateInfo.ppEnabledLayerNames = deviceLayers.data();
//	deviceCreateInfo.enabledLayerCount = static_cast<uint32>(deviceLayers.size());
//
//	VkDevice device;
//	vkCreateDevice(selectPhysicalDevice, &deviceCreateInfo, nullptr, &device);
//	assert(device != VK_NULL_HANDLE);
//	
//	VkQueue queue;
//	vkGetDeviceQueue(device, graphicsQueueIndex, 0, &queue);
//}

}