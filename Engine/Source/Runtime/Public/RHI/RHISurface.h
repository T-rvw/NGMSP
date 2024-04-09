#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHISurface;

/// <summary>
/// RHISurface allows bind all draw calls to a specific platform window.
/// Vulkan : VkSurface
/// D3D12 : ID3D12Resource
/// Metal : CAMetalLayer
/// </summary>
class RHI_API RHISurface
{
public:
	RHISurface();
	RHISurface(const RHISurface&) = delete;
	RHISurface& operator=(const RHISurface&) = delete;
	RHISurface(RHISurface&& other) noexcept;
	RHISurface& operator=(RHISurface&& other) noexcept;
	~RHISurface();

	void Reset(std::unique_ptr<IRHISurface>&& impl);
	void* GetHandle() const;

private:
	IRHISurface* m_pImpl = nullptr;
};

}