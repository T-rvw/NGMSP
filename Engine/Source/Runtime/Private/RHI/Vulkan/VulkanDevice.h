#pragma once

#include "../IRHIDevice.h"

namespace ow
{

struct RHIDeviceCreateInfo;

class VulkanDevice : public IRHIDevice
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