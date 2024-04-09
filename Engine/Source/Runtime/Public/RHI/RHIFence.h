#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIFence;

/// <summary>
/// RHIFence is used to synchronize the CPU and GPU.
/// Vulkan : VkFence
/// D3D12 : ID3D12Fence
/// Metal : MTLFence
/// </summary>
class RHI_API RHIFence
{
public:
	RHIFence();
	RHIFence(const RHIFence&) = delete;
	RHIFence& operator=(const RHIFence&) = delete;
	RHIFence(RHIFence&& other) noexcept;
	RHIFence& operator=(RHIFence&& other) noexcept;
	~RHIFence();

	void Reset(std::unique_ptr<IRHIFence>&& impl);

private:
	IRHIFence* m_pImpl = nullptr;
};

}