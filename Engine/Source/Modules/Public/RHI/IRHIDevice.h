#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

#ifdef CreateSemaphore
#undef CreateSemaphore
#endif

class IRHIDevice : public RefCountObject
{
public:
	virtual ~IRHIDevice() {}

	virtual BarrierHandle CreateBarrier(const RHIBarrierCreateInfo& createInfo) = 0;
	virtual BufferHandle CreateBuffer(const RHIBufferCreateInfo& createInfo) = 0;
	virtual CommandPoolHandle CreateCommandPool(const RHICommandPoolCreateInfo& createInfo) = 0;
	virtual FenceHandle CreateFence(const RHIFenceCreateInfo& createInfo) = 0;
	virtual PipelineLayoutHandle CreatePipelineLayout(const RHIPipelineLayoutCreateInfo& createInfo) = 0;
	virtual SemaphoreHandle CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) = 0;
	virtual SwapChainHandle CreateSwapChain(const RHISwapChainCreateInfo& createInfo) = 0;
	virtual TextureHandle CreateTexture(const RHITextureCreateInfo& createInfo) = 0;
	virtual CommandQueueHandle GetCommandQueue(RHICommandType commandType) const = 0;
};

}