#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHICommandList.h>

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

	virtual void Init() override;
};

}