#include "VulkanInstance.h"

#include "VulkanAdapter.h"

#include <RHI/RHIAdapter.h>
#include <RHI/RHITypes.h>

namespace ow
{

VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(m_instance, nullptr);
}

RHIBackend VulkanInstance::GetBackend() const
{
	return RHIBackend::Vulkan;
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
	applicationInfo.pApplicationName = "Vulkan Sample application";
	applicationInfo.pEngineName = "Vulkan Sample Engine";

	VkInstanceCreateInfo instanceCreateInfo {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
	instanceCreateInfo.enabledLayerCount = static_cast<uint32_t> (instanceLayers.size());
	instanceCreateInfo.pApplicationInfo = &applicationInfo;

	VK_VERIFY(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));
	assert(m_instance != VK_NULL_HANDLE);
}

std::vector<std::unique_ptr<RHIAdapter>> VulkanInstance::EnumAdapters() const
{
	uint32 physicalDeviceCount = 0;
	VK_VERIFY(vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	VK_VERIFY(vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, physicalDevices.data()));

	std::vector<std::unique_ptr<RHIAdapter>> rhiAdapters;
	for (const auto physicalDevice : physicalDevices)
	{
		VkPhysicalDeviceProperties properties {};
		vkGetPhysicalDeviceProperties(physicalDevice, &properties);
		
		VkPhysicalDeviceMemoryProperties memoryProperties {};
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

		auto vkAdapter = std::make_unique<VulkanAdapter>(physicalDevice);
		vkAdapter->SetName(properties.deviceName);
		vkAdapter->SetType(properties.deviceType);
		vkAdapter->SetVendor(properties.vendorID);

		const bool isIntegratedGPU = GPUAdapterType::Integrated == vkAdapter->GetType();
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

		vkAdapter->SetVideoMemorySize(videoMemorySize);
		vkAdapter->SetSystemMemorySize(systemMemorySize);
		vkAdapter->SetSharedMemorySize(sharedMemorySize);

		auto& rhiAdapter = rhiAdapters.emplace_back(std::make_unique<RHIAdapter>());
		rhiAdapter->Reset(MoveTemp(vkAdapter));
	}

	return rhiAdapters;
}

}