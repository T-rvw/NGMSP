#pragma once

#include "VulkanHeader.h"

#include <RHI/Interfaces/IRHITexture.h>

namespace ow
{

class VulkanTexture : public IRHITexture
{
public:
	VulkanTexture() = default;
	VulkanTexture(const VulkanTexture&) = delete;
	VulkanTexture& operator=(const VulkanTexture&) = delete;
	VulkanTexture(VulkanTexture&&) = default;
	VulkanTexture& operator=(VulkanTexture&&) = default;
	virtual ~VulkanTexture();

	virtual void Init() override;
};

}