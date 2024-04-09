#include "VulkanInstance.h"

#include "VulkanAdapter.h"
#include "VulkanSurface.h"

#include <RHI/RHIAdapter.h>
#include <RHI/RHISurface.h>
#include <RHI/RHITypes.h>

#include <optional>

namespace
{

VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	UNUSED(messageType);
	UNUSED(pUserData);

	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		printf("[Vulkan Warning] : %s \n", pCallbackData->pMessage);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		printf("[Vulkan Error] : %s \n", pCallbackData->pMessage);
	}

	return VK_FALSE;
}

}

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

	// Load vulkan api entry points from module dynamically.
	VK_VERIFY(volkInitialize());

	// Enable instance layers.
	uint32 instanceLayerCount;
	VK_VERIFY(vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr));
	std::vector<VkLayerProperties> availableInstanceLayers(instanceLayerCount);
	VK_VERIFY(vkEnumerateInstanceLayerProperties(&instanceLayerCount, availableInstanceLayers.data()));

	std::vector<const char*> instanceLayers;
	for (const auto& availableInstanceLayer : availableInstanceLayers)
	{
		if (createInfo.Validation != RHIValidationMode::Disabled)
		{
			if (0 == strcmp(availableInstanceLayer.layerName, "VK_LAYER_KHRONOS_validation"))
			{
				instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
				break;
			}
			else if (0 == strcmp(availableInstanceLayer.layerName, "VK_LAYER_LUNARG_standard_validation"))
			{
				instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
				break;
			}
			else if (0 == strcmp(availableInstanceLayer.layerName, "VK_LAYER_LUNARG_core_validation"))
			{
				instanceLayers.push_back("VK_LAYER_LUNARG_core_validation");
				break;
			}
		}
	}

	// Debug utils.
	std::optional<VkDebugUtilsMessengerCreateInfoEXT> optDebugUtilsCreateInfo;
	
	// Enable instance extensions.
	uint32_t extensionCount;
	VK_VERIFY(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));
	std::vector<VkExtensionProperties> availableInstanceExtensions(extensionCount);
	VK_VERIFY(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableInstanceExtensions.data()));

	std::vector<const char*> instanceExtensions;
	for (const auto& availableExtension : availableInstanceExtensions)
	{
		if (createInfo.Debug != RHIDebugMode::Disabled)
		{
			if (0 == strcmp(availableExtension.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
			{
				instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

				VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo {};
				debugUtilsCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
				debugUtilsCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
				debugUtilsCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
				debugUtilsCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
				debugUtilsCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
				debugUtilsCreateInfo.pfnUserCallback = DebugUtilsMessengerCallback;
				optDebugUtilsCreateInfo = debugUtilsCreateInfo;
			}
			else if (0 == strcmp(availableExtension.extensionName, VK_EXT_DEBUG_REPORT_EXTENSION_NAME))
			{
				instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			}
		}

		if (0 == strcmp(availableExtension.extensionName, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
		{
			instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
		}
		else if (0 == strcmp(availableExtension.extensionName, VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME))
		{
			instanceExtensions.push_back(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);
		}
		else if (0 == strcmp(availableExtension.extensionName, VK_KHR_SURFACE_EXTENSION_NAME))
		{
			instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
		}
#ifdef PLATFORM_WINDOWS
		else if (0 == strcmp(availableExtension.extensionName, VK_KHR_WIN32_SURFACE_EXTENSION_NAME))
		{
			instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
		}
#endif
	}

	// Dump
	{
		printf("[VulkanInstance]\n");
		printf("\t[Layers]\n");
		for (const auto& instanceLayer : instanceLayers)
		{
			printf("\t\t%s\n", instanceLayer);
		}

		printf("\t[Extensions]\n");
		for (const auto& instanceExtension : instanceExtensions)
		{
			printf("\t\t%s\n", instanceExtension);
		}
		printf("\n");
	}

	// Create instance.
	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion = VK_API_VERSION_1_3;
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pApplicationName = "Hamster Graphics";
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = "Hamster Engine";

	VkInstanceCreateInfo instanceCreateInfo {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
	instanceCreateInfo.enabledLayerCount = static_cast<uint32_t> (instanceLayers.size());
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	if (optDebugUtilsCreateInfo.has_value())
	{
		instanceCreateInfo.pNext = &optDebugUtilsCreateInfo.value();
	}

	VK_VERIFY(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));
	assert(m_instance != VK_NULL_HANDLE);
	volkLoadInstanceOnly(m_instance);

	if (optDebugUtilsCreateInfo.has_value())
	{
		VkDebugUtilsMessengerEXT debugUtilsMessenger = VK_NULL_HANDLE;
		vkCreateDebugUtilsMessengerEXT(m_instance, &optDebugUtilsCreateInfo.value(), nullptr, &debugUtilsMessenger);
		assert(debugUtilsMessenger != VK_NULL_HANDLE);
	}
}

std::vector<RHIAdapter> VulkanInstance::EnumerateAdapters() const
{
	uint32 physicalDeviceCount = 0;
	VK_VERIFY(vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	VK_VERIFY(vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, physicalDevices.data()));

	std::vector<RHIAdapter> rhiAdapters;
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
		vkAdapter->SetDeviceID(properties.deviceID);

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

		auto& rhiAdapter = rhiAdapters.emplace_back();
		rhiAdapter.Reset(MoveTemp(vkAdapter));
	}

	return rhiAdapters;
}

RHISurface VulkanInstance::CreateSurface(void* pPlatformWindowHandle, void* pPlatformInstanceHandle) const
{
	VkSurfaceKHR vkSurface;

#ifdef PLATFORM_WINDOWS
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = (HWND)pPlatformWindowHandle;
	surfaceCreateInfo.hinstance = (HINSTANCE)pPlatformInstanceHandle;
	VK_VERIFY(vkCreateWin32SurfaceKHR(m_instance, &surfaceCreateInfo, nullptr, &vkSurface));
#else
	static_assert("Unsupported platform to create surface.");
#endif

	auto vulkanSurface = std::make_unique<VulkanSurface>(m_instance, vkSurface);

	RHISurface rhiSurface;
	rhiSurface.Reset(MoveTemp(vulkanSurface));
	return rhiSurface;
}

}