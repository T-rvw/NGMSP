#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIFramebuffer;

/// <summary>
/// RHIFramebuffer is a group of output textures used by raster based graphics pipeline.
/// Vulkan : VkFramebuffer
/// D3D12 : ID3D12Resource
/// Metal : CAMetalLayer
/// </summary>
class RHI_API RHIFramebuffer
{
public:
	RHIFramebuffer();
	RHIFramebuffer(const RHIFramebuffer&) = delete;
	RHIFramebuffer& operator=(const RHIFramebuffer&) = delete;
	RHIFramebuffer(RHIFramebuffer&& other) noexcept;
	RHIFramebuffer& operator=(RHIFramebuffer&& other) noexcept;
	~RHIFramebuffer();

	void Reset(std::unique_ptr<IRHIFramebuffer>&& impl);
	void* GetHandle() const;

private:
	IRHIFramebuffer* m_pImpl = nullptr;
};

}