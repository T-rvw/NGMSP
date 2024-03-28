#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHICommandQueue.h>

namespace ow
{

class VulkanCommandQueue : public IRHICommandQueue
{
public:
	VulkanCommandQueue() = default;
	VulkanCommandQueue(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue& operator=(const VulkanCommandQueue&) = delete;
	VulkanCommandQueue(VulkanCommandQueue&&) = default;
	VulkanCommandQueue& operator=(VulkanCommandQueue&&) = default;
	virtual ~VulkanCommandQueue();

	virtual void Init() override;
};

}