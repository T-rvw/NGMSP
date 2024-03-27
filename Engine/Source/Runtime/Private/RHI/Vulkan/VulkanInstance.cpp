#include "VulkanInstance.h"

#include "VulkanDevice.h"

#include <RHI/RHIDevice.h>
#include <RHI/RHITypes.h>

namespace ow
{

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
		instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
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

	vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
}

void VulkanInstance::Shutdown()
{
	if (m_instance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_instance, nullptr);
		m_instance = VK_NULL_HANDLE;
	}
}

int32 VulkanInstance::GetDeviceCount() const
{
	return static_cast<int32>(m_devices.size());
}

RHIDevice* VulkanInstance::GetDevice(int32 index)
{
	assert(index < m_devices.size());
	return &m_devices[index];
}

}