#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIAdapter.h>

namespace ow
{

class RHIDevice;

class VulkanAdapter : public IRHIAdapter
{
public:
	VulkanAdapter() = default;
	explicit VulkanAdapter(VkPhysicalDevice physcialDevice);
	VulkanAdapter(const VulkanAdapter&) = delete;
	VulkanAdapter& operator=(const VulkanAdapter&) = delete;
	VulkanAdapter(VulkanAdapter&&) = default;
	VulkanAdapter& operator=(VulkanAdapter&&) = default;
	virtual ~VulkanAdapter();

	virtual void Init() override;
	virtual void* GetHandle() const override { return m_physcialDevice; }

	GPUAdapterType GetType() const;
	void SetType(VkPhysicalDeviceType deviceType);

	std::unique_ptr<RHIDevice> CreateDevice(const RHIDeviceCreateInfo& createInfo) const;

private:
	VkPhysicalDevice m_physcialDevice = VK_NULL_HANDLE;
};

}