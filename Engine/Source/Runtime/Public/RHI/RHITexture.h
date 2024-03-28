#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHITexture;

/// <summary>
/// RHITexture is a continus data which presents color information in a specific format.
/// Vulkan : VkImage & VkImageView
/// D3D12 : ID3D12Resource
/// Metal : MTLTexture
/// </summary>
class RHI_API RHITexture
{
public:
	RHITexture();
	RHITexture(const RHITexture&) = delete;
	RHITexture& operator=(const RHITexture&) = delete;
	RHITexture(RHITexture&& other) noexcept;
	RHITexture& operator=(RHITexture&& other) noexcept;
	~RHITexture();

	void Init();

private:
	IRHITexture* m_pImpl = nullptr;
};

}