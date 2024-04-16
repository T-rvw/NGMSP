#include "VulkanInstance.h"

#include "VulkanAdapter.h"

#include <RHI/IRHIAdapter.h>
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
	vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugUtilsMessenger, nullptr);
	vkDestroyInstance(m_instance, nullptr);
}

RHIBackend VulkanInstance::GetBackend() const
{
	return RHIBackend::Vulkan;
}

void VulkanInstance::Init(const RHIInstanceCreateInfo& createInfo)
{
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

	// Enable instance extensions.
	uint32_t extensionCount;
	VK_VERIFY(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));
	m_availableExtensions.resize(extensionCount);
	VK_VERIFY(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_availableExtensions.data()));

	std::vector<const char*> instanceExtensions;
	EnableExtensionSafely(instanceExtensions, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
	EnableExtensionSafely(instanceExtensions, VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);
	EnableExtensionSafely(instanceExtensions, VK_KHR_SURFACE_EXTENSION_NAME);
#ifdef VK_USE_PLATFORM_WIN32_KHR
	EnableExtensionSafely(instanceExtensions, VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
	EnableExtensionSafely(instanceExtensions, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	EnableExtensionSafely(instanceExtensions, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
	EnableExtensionSafely(instanceExtensions, VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
	EnableExtensionSafely(instanceExtensions, VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	EnableExtensionSafely(instanceExtensions, VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	EnableExtensionSafely(instanceExtensions, VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#endif

	// Debug utils.
	std::optional<VkDebugUtilsMessengerCreateInfoEXT> optDebugUtilsCreateInfo;
	if (createInfo.Debug != RHIDebugMode::Disabled &&
		EnableExtensionSafely(instanceExtensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
	{
		VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo{};
		debugUtilsCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugUtilsCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
		debugUtilsCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugUtilsCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
		debugUtilsCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
		debugUtilsCreateInfo.pfnUserCallback = DebugUtilsMessengerCallback;
		optDebugUtilsCreateInfo = debugUtilsCreateInfo;
	}

	uint32 maxAPIVersion;
	vkEnumerateInstanceVersion(&maxAPIVersion);

	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion = maxAPIVersion;
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
		VK_VERIFY(vkCreateDebugUtilsMessengerEXT(m_instance, &optDebugUtilsCreateInfo.value(), nullptr, &m_debugUtilsMessenger));
		assert(m_debugUtilsMessenger != VK_NULL_HANDLE);
	}

	InitAdapters();
}

void VulkanInstance::InitAdapters()
{
	uint32 adapterCount;
	VK_VERIFY(vkEnumeratePhysicalDevices(m_instance, &adapterCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(adapterCount);
	VK_VERIFY(vkEnumeratePhysicalDevices(m_instance, &adapterCount, physicalDevices.data()));

	for (uint32 adapterIndex = 0; adapterIndex < adapterCount; ++adapterIndex)
	{
		m_adapters.emplace_back(physicalDevices[adapterIndex]);
	}
}

void VulkanInstance::EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters)
{
	if (nullptr == pAdapters)
	{
		adapterCount = static_cast<uint32>(m_adapters.size());
		return;
	}

	for (uint32 adapterIndex = 0; adapterIndex < adapterCount; ++adapterIndex)
	{
		pAdapters[adapterIndex] = &m_adapters[adapterIndex];
	}
}

bool VulkanInstance::EnableExtensionSafely(std::vector<const char*>& extensions, const char* pExtensionName) const
{
	if (!VulkanUtils::FindExtension(m_availableExtensions, pExtensionName))
	{
		return false;
	}

	extensions.push_back(pExtensionName);
	return true;
}

}