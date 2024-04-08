#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHICommandPool;

/// <summary>
/// RHICommandPool is a data structure that allows you to create RHICommandBuffers.
/// Vulkan : VkCommandPool
/// D3D12 : ID3D12CommandAllocator
/// Metal : MTLCommandQueue
/// </summary>
class RHI_API RHICommandPool
{
public:
	RHICommandPool();
	RHICommandPool(const RHICommandPool&) = delete;
	RHICommandPool& operator=(const RHICommandPool&) = delete;
	RHICommandPool(RHICommandPool&& other) noexcept;
	RHICommandPool& operator=(RHICommandPool&& other) noexcept;
	~RHICommandPool();

	void Init();

private:
	IRHICommandPool* m_pImpl = nullptr;
};

}