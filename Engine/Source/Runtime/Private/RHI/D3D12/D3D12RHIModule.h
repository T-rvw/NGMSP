#pragma once

#include "D3D12Adapter.h"
#include "D3D12Buffer.h"
#include "D3D12CommandQueue.h"
#include "D3D12Device.h"
#include "D3D12Fence.h"
#include "D3D12Instance.h"
#include "D3D12Semaphore.h"
#include "D3D12SwapChain.h"
#include "D3D12Texture.h"

#include <RHI/IRHIModule.h>

#include <list>
#include <memory>

namespace ow
{

class D3D12RHIModule : public IRHIModule
{
public:
	virtual void Shutdown() override;

	virtual IRHIInstance* CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) override;
	virtual IRHIDevice* CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) override;

	virtual IRHICommandQueue* CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) override;
	virtual IRHISwapChain* CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) override;

	virtual IRHIFence* CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) override;
	virtual IRHISemaphore* CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) override;

	virtual IRHIBuffer* CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) override;
	virtual IRHISampler* CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) override;
	virtual IRHITexture* CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) override;

private:
	std::list<std::unique_ptr<D3D12Instance>> m_rhiInstances;
	std::list<std::unique_ptr<D3D12Device>> m_rhiDevices;
	std::list<std::unique_ptr<D3D12CommandQueue>> m_rhiCommandQueues;
	std::list<std::unique_ptr<D3D12SwapChain>> m_rhiSwapChains;
	std::list<std::unique_ptr<D3D12Fence>> m_rhiFences;
	std::list<std::unique_ptr<D3D12Semaphore>> m_rhiSemaphores;
	std::list<std::unique_ptr<D3D12Buffer>> m_rhiBuffer;
	std::list<std::unique_ptr<D3D12Texture>> m_rhiTextures;
};

}