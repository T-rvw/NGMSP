#pragma once

#include <Core/Base/RefCountPtr.h>
#include <Core/Modules/IModule.h>

namespace ow
{

struct RHIBufferCreateInfo;
struct RHICommandQueueCreateInfo;
struct RHIDeviceCreateInfo;
struct RHIFenceCreateInfo;
struct RHIInstanceCreateInfo;
struct RHISamplerCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHISwapChainCreateInfo;
struct RHITextureCreateInfo;

class IRHIAdapter;
class IRHIBuffer;
class IRHICommandQueue;
class IRHIDevice;
class IRHIFence;
class IRHIInstance;
class IRHISampler;
class IRHISemaphore;
class IRHISwapChain;
class IRHITexture;

class IRHIModule : public IModule, public RefCountObject
{
public:
	virtual ~IRHIModule() {}

	virtual RefCountPtr<IRHIInstance> CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHIDevice> CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHICommandQueue> CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHISwapChain> CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHIFence> CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHISemaphore> CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHIBuffer> CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHISampler> CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) = 0;
	virtual RefCountPtr<IRHITexture> CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) = 0;
};

}