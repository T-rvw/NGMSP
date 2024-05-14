#include "VulkanAccelerationStructure.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanAccelerationStructure::VulkanAccelerationStructure(const VulkanDevice* pDevice, const RHIAccelerationStructureCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
}

VulkanAccelerationStructure::~VulkanAccelerationStructure()
{
}

}