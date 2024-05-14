#pragma once

#include "VulkanAdapter.h"

#include <RHI//IRHIInstance.h>

namespace ow
{

class IRHIAdapter;
enum class RHIBackend;
struct RHIInstanceCreateInfo;

class VulkanInstance : public IRHIInstance
{
public:
	VulkanInstance() = delete;
	VulkanInstance(const RHIInstanceCreateInfo& createInfo);
	VulkanInstance(const VulkanInstance&) = delete;
	VulkanInstance& operator=(const VulkanInstance&) = delete;
	VulkanInstance(VulkanInstance&&) = default;
	VulkanInstance& operator=(VulkanInstance&&) = default;
	virtual ~VulkanInstance();

	virtual RHIBackend GetBackend() const override;
	virtual void EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters) override;

	VkInstance GetHandle() const { return m_instance; }
	const Vector<VkExtensionProperties>& GetAvaialableExtensions() const { return m_availableExtensions; }
	const Vector<VkLayerProperties>& GetAvaialableLayers() const { return m_availableLayers; }

private:
	void Init();
	void InitAdapters();

private:
	VkInstance m_instance;
	VkDebugUtilsMessengerEXT m_debugUtilsMessenger;
	Vector<VkExtensionProperties> m_availableExtensions;
	Vector<VkLayerProperties> m_availableLayers;
	Vector<VulkanAdapter> m_adapters;
};

}