#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHISemaphore;

/// <summary>
/// RHISemaphore is used to introduce dependencies between operations, such as
/// waiting before acquiring the next image in the swapchain before submitting command buffers to your device queue.
/// Vulkan : VkSemaphore
/// D3D12 : PlatformSemaphore
/// Metal : PlatformSemaphore
/// </summary>
class RHI_API RHISemaphore
{
public:
	RHISemaphore();
	RHISemaphore(const RHISemaphore&) = delete;
	RHISemaphore& operator=(const RHISemaphore&) = delete;
	RHISemaphore(RHISemaphore&& other) noexcept;
	RHISemaphore& operator=(RHISemaphore&& other) noexcept;
	~RHISemaphore();

	void Reset(std::unique_ptr<IRHISemaphore> impl);

private:
	IRHISemaphore* m_pImpl = nullptr;
};

}