#pragma once

#include "VulkanHeader.h"

#include <RHI/IRHIAccelerationStructure.h>

namespace ow
{

class VulkanDevice;

class VulkanAccelerationStructure : public IRHIAccelerationStructure
{
public:
	VulkanAccelerationStructure() = default;
	explicit VulkanAccelerationStructure(const VulkanDevice* pDevice, const RHIAccelerationStructureCreateInfo& createInfo);
	VulkanAccelerationStructure(const VulkanAccelerationStructure&) = delete;
	VulkanAccelerationStructure& operator=(const VulkanAccelerationStructure&) = delete;
	VulkanAccelerationStructure(VulkanAccelerationStructure&&) = default;
	VulkanAccelerationStructure& operator=(VulkanAccelerationStructure&&) = default;
	virtual ~VulkanAccelerationStructure();

private:
	const VulkanDevice* m_pDevice;
};

}