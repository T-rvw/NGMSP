#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHICommandList;

/// <summary>
/// RHICommandLists are groups of command buffers pushed in batches to the GPU.
/// Vulkan : VkSubmitInfo
/// D3D12 : ID3D12CommandList[]
/// Metal : MTLCommandBuffer
/// </summary>
class RHI_API RHICommandList
{
public:
	RHICommandList();
	RHICommandList(const RHICommandList&) = delete;
	RHICommandList& operator=(const RHICommandList&) = delete;
	RHICommandList(RHICommandList&& other) noexcept;
	RHICommandList& operator=(RHICommandList&& other) noexcept;
	~RHICommandList();

	void Init();

private:
	IRHICommandList* m_pImpl = nullptr;
};

}