#include "VulkanCommandQueue.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandQueue::VulkanCommandQueue(const VulkanDevice* pDevice, const RHICommandQueueCreateInfo& createInfo)
{
	vkGetDeviceQueue(pDevice->GetHandle(), createInfo.ID, 0, &m_queue);
}

}