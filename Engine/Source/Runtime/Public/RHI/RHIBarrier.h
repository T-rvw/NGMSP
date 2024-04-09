#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIBarrier;

/// <summary>
/// RHIBarrier is a more granular form of synchronization than RHIFence, used inside command buffers.
/// Vulkan : VkCmdPipelineBarrier
/// D3D12 : D3D12_RESOURCE_BARRIER
/// Metal : MTLFence
/// </summary>
class RHI_API RHIBarrier
{
public:
	RHIBarrier();
	RHIBarrier(const RHIBarrier&) = delete;
	RHIBarrier& operator=(const RHIBarrier&) = delete;
	RHIBarrier(RHIBarrier&& other) noexcept;
	RHIBarrier& operator=(RHIBarrier&& other) noexcept;
	~RHIBarrier();

	void Reset(std::unique_ptr<IRHIBarrier>&& impl);

private:
	IRHIBarrier* m_pImpl = nullptr;
};

}