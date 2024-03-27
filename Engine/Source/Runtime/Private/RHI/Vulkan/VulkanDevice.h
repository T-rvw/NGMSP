#pragma once

namespace ow
{

struct RHIDeviceCreateInfo;

class VulkanDevice
{
public:
	VulkanDevice() = default;
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	~VulkanDevice() = default;

	void Init(const RHIDeviceCreateInfo& createInfo);
};

}