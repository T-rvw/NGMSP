#pragma once

#include "VulkanHeader.h"
#include "../IRHIInstance.h"

namespace ow
{

class RHIDevice;
struct RHIInstanceCreateInfo;

class VulkanInstance : public IRHIInstance
{
public:
	VulkanInstance() = default;
	VulkanInstance(const VulkanInstance&) = delete;
	VulkanInstance& operator=(const VulkanInstance&) = delete;
	VulkanInstance(VulkanInstance&&) = default;
	VulkanInstance& operator=(VulkanInstance&&) = default;
	~VulkanInstance() = default;

	virtual void Init(const RHIInstanceCreateInfo& createInfo) override;
	virtual void Shutdown() override;

	virtual int32 GetDeviceCount() const override;
	virtual RHIDevice* GetDevice(int32 index) override;

private:
	VkInstance m_instance = VK_NULL_HANDLE;
	std::vector<RHIDevice> m_devices;
};

}