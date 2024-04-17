#pragma once

#include <Core/HAL/BasicTypes.h>
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

class RHI_API IRHIModule : public IModule
{
public:
	virtual ~IRHIModule() {}

	virtual IRHIInstance* CreateRHIInstance(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual IRHIDevice* CreateRHIDevice(IRHIAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) = 0;

	virtual IRHISwapChain* CreateRHISwapChain(IRHIDevice* pDevice, const RHISwapChainCreateInfo& createInfo) = 0;
	virtual IRHICommandQueue* CreateRHICommandQueue(IRHIDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) = 0;

	virtual IRHIFence* CreateRHIFence(IRHIDevice* pDevice, const RHIFenceCreateInfo& createInfo) = 0;
	virtual IRHISemaphore* CreateRHISemaphore(IRHIDevice* pDevice, const RHISemaphoreCreateInfo& createInfo) = 0;

	virtual IRHIBuffer* CreateRHIBuffer(IRHIDevice* pDevice, const RHIBufferCreateInfo& createInfo) = 0;
	virtual IRHISampler* CreateRHISampler(IRHIDevice* pDevice, const RHISamplerCreateInfo& createInfo) = 0;
	virtual IRHITexture* CreateRHITexture(IRHIDevice* pDevice, const RHITextureCreateInfo& createInfo) = 0;
};

}