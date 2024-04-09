#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIDevice;
class RHICommandQueue;
class RHIFence;
class RHISemaphore;
class RHISwapChain;

/// <summary>
/// RHIDevice is a logical device which helps to create graphics resources, submit draw/compute/.. commands.
/// Vulkan : VkDevice
/// D3D12 : ID3D12Device
/// Metal : MTLDevice
/// </summary>
class RHI_API RHIDevice
{
public:
	RHIDevice();
	explicit RHIDevice(std::unique_ptr<IRHIDevice> impl);
	RHIDevice(const RHIDevice&) = delete;
	RHIDevice& operator=(const RHIDevice&) = delete;
	RHIDevice(RHIDevice&& other) noexcept;
	RHIDevice& operator=(RHIDevice&& other) noexcept;
	~RHIDevice();

	void Reset(std::unique_ptr<IRHIDevice>&& impl);
	void Dump() const;
	void* GetHandle() const;
	RHICommandQueue CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const;
	RHIFence CreateFence() const;
	RHISemaphore CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) const;
	RHISwapChain CreateSwapChain(const RHISwapChainCreateInfo& createInfo) const;

private:
	IRHIDevice* m_pImpl = nullptr;
};

}