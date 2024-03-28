#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIDevice.h>

namespace ow
{

class VulkanDevice : public IRHIDevice
{
public:
	VulkanDevice() = default;
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	virtual ~VulkanDevice();

	virtual void Init() override;
	virtual void* GetHandle() const override { return m_device; }

private:
	VkDevice m_device = VK_NULL_HANDLE;
};

}