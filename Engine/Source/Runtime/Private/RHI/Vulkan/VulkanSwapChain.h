#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHISwapChain.h>

namespace ow
{

class VulkanSwapChain : public IRHISwapChain
{
public:
	VulkanSwapChain() = default;
	VulkanSwapChain(const VulkanSwapChain&) = delete;
	VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
	VulkanSwapChain(VulkanSwapChain&&) = default;
	VulkanSwapChain& operator=(VulkanSwapChain&&) = default;
	virtual ~VulkanSwapChain();

	virtual void Init() override;
};

}