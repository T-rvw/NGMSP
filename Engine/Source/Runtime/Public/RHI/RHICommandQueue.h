#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHICommandQueue;

/// <summary>
/// RHICommandQueue allows to enqueue commands for GPU to execute.
/// Vulkan : VkQueue
/// D3D12 : ID3D12CommandQueue
/// Metal : MTLCommandQueue
/// </summary>
class RHI_API RHICommandQueue
{
public:
	RHICommandQueue();
	RHICommandQueue(const RHICommandQueue&) = delete;
	RHICommandQueue& operator=(const RHICommandQueue&) = delete;
	RHICommandQueue(RHICommandQueue&& other) noexcept;
	RHICommandQueue& operator=(RHICommandQueue&& other) noexcept;
	~RHICommandQueue();

	void Init();

private:
	IRHICommandQueue* m_pImpl = nullptr;
};

}