#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIBuffer;

/// <summary>
/// RHIBuffer is a continus data in specific layout based on usages, such as mesh vertex buffer, mesh index buffer.
/// Vulkan : VkBuffer & VkBufferView
/// D3D12 : ID3D12Resource
/// Metal : MTLBuffer
/// </summary>
class RHI_API RHIBuffer
{
public:
	RHIBuffer();
	RHIBuffer(const RHIBuffer&) = delete;
	RHIBuffer& operator=(const RHIBuffer&) = delete;
	RHIBuffer(RHIBuffer&& other) noexcept;
	RHIBuffer& operator=(RHIBuffer&& other) noexcept;
	~RHIBuffer();

	void Init();

private:
	IRHIBuffer* m_pImpl = nullptr;
};

}