#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHIInstance.h>

namespace ow
{

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
	virtual void* GetHandle() const override { return m_instance; }

	virtual std::vector<RHIAdapter> EnumAdapters() const override;

private:
	VkInstance m_instance = VK_NULL_HANDLE;
};

}