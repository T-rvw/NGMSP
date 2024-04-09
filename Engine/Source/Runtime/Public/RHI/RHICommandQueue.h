#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHICommandQueue;

/// <summary>
/// RHICommandQueue enqueues commands to execute on GPU.
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
	void Reset(std::unique_ptr<IRHICommandQueue> impl);
	void Dump() const;
	void* GetHandle() const;

	void SetType(RHICommandType commandQueueType);
	RHICommandType GetType() const;

private:
	IRHICommandQueue* m_pImpl = nullptr;
};

}