#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandList.h>

namespace ow
{

class VulkanCommandList : public IRHICommandList
{
public:
	VulkanCommandList() = default;
	VulkanCommandList(const VulkanCommandList&) = delete;
	VulkanCommandList& operator=(const VulkanCommandList&) = delete;
	VulkanCommandList(VulkanCommandList&&) = default;
	VulkanCommandList& operator=(VulkanCommandList&&) = default;
	virtual ~VulkanCommandList();
};

}