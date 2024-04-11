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
	VulkanInstance() = default;
	VulkanInstance(const VulkanInstance&) = delete;
	VulkanInstance& operator=(const VulkanInstance&) = delete;
	VulkanInstance(VulkanInstance&&) = default;
	VulkanInstance& operator=(VulkanInstance&&) = default;
	virtual ~VulkanInstance();

	virtual void Init(const RHIInstanceCreateInfo& createInfo) override;

	virtual RHIBackend GetBackend() const override;
	virtual void EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters) override;

private:
	void InitAdapters();

private:
	VkDebugUtilsMessengerEXT m_debugUtilsMessenger = VK_NULL_HANDLE;
	VkInstance m_instance = VK_NULL_HANDLE;

	std::vector<VulkanAdapter> m_adapters;
};

}