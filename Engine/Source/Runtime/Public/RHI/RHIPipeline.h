#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIPipeline;

/// <summary>
/// RHIPipeline is a description of what will be executed when performing a raster draw call, compute dispath, ray tracing dispath, ...
/// Vulkan : VkPhyscialDevice
/// D3D12 : IDXGIAdapter(n)
/// Metal : MTLDevice
/// </summary>
class RHI_API RHIPipeline
{
public:
	RHIPipeline();
	RHIPipeline(const RHIPipeline&) = delete;
	RHIPipeline& operator=(const RHIPipeline&) = delete;
	RHIPipeline(RHIPipeline&& other) noexcept;
	RHIPipeline& operator=(RHIPipeline&& other) noexcept;
	~RHIPipeline();

	void Init();

private:
	IRHIPipeline* m_pImpl = nullptr;
};

}