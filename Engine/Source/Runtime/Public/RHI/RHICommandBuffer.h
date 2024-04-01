#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHICommandBuffer;

/// <summary>
/// RHICommandBuffer is an async computing unit where you describe procedures for the GPU to execute,
/// such as draw calls, copy data, ...
/// Vulkan : VkCommandBuffer
/// D3D12 : ID3D12GraphicsCommandList
/// Metal : MTLRenderCommandEncoder
/// </summary>
class RHI_API RHICommandBuffer
{
public:
	RHICommandBuffer();
	RHICommandBuffer(const RHICommandBuffer&) = delete;
	RHICommandBuffer& operator=(const RHICommandBuffer&) = delete;
	RHICommandBuffer(RHICommandBuffer&& other) noexcept;
	RHICommandBuffer& operator=(RHICommandBuffer&& other) noexcept;
	~RHICommandBuffer();

	void Init();

private:
	IRHICommandBuffer* m_pImpl = nullptr;
};

}