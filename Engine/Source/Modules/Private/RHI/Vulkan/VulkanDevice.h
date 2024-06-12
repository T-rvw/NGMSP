#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHIDevice.h>

namespace ow
{

class VulkanAdapter;
class VulkanCommandQueue;

class VulkanDevice : public IRHIDevice
{
public:
	VulkanDevice() = delete;
	explicit VulkanDevice(const VulkanAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo);
	VulkanDevice(const VulkanDevice&) = delete;
	VulkanDevice& operator=(const VulkanDevice&) = delete;
	VulkanDevice(VulkanDevice&&) = default;
	VulkanDevice& operator=(VulkanDevice&&) = default;
	virtual ~VulkanDevice();

	VkDevice GetHandle() const { return m_device; }
	VkPhysicalDevice GetAdapter() const;
	VkInstance GetInstance() const;

	virtual BarrierHandle CreateBarrier(const RHIBarrierCreateInfo& createInfo) override;
	virtual BufferHandle CreateBuffer(const RHIBufferCreateInfo& createInfo) override;
	virtual FenceHandle CreateFence(const RHIFenceCreateInfo& createInfo) override;
	virtual CommandPoolHandle CreateCommandPool(const RHICommandPoolCreateInfo& createInfo) override;
	virtual PipelineLayoutHandle CreatePipelineLayout(const RHIPipelineLayoutCreateInfo& createInfo) override;
	virtual SemaphoreHandle CreateSemaphore(const RHISemaphoreCreateInfo& createInfo) override;
	virtual SwapChainHandle CreateSwapChain(const RHISwapChainCreateInfo& createInfo) override;
	virtual TextureHandle CreateTexture(const RHITextureCreateInfo& createInfo) override;
	virtual CommandQueueHandle GetCommandQueue(RHICommandType commandType) const;
	
private:
	const VulkanAdapter* m_pAdapter;
	VkDevice m_device;

	RefCountPtr<VulkanCommandQueue> m_commandQueues[EnumCount<RHICommandType>()];
};

}