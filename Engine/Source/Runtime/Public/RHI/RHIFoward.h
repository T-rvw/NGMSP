#pragma once

#include <Core/Base/RefCountPtr.h>
#include <RHI/RHIEnums.h>

namespace ow
{

struct RHIBarrierCreateInfo;
struct RHIBufferCreateInfo;
struct RHICommandBufferCreateInfo;
struct RHICommandPoolCreateInfo;
struct RHICommandQueueCreateInfo;
struct RHIDeviceCreateInfo;
struct RHIFenceCreateInfo;
struct RHIInstanceCreateInfo;
struct RHISamplerCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHIShaderCreateInfo;
struct RHISwapChainCreateInfo;
struct RHITextureCreateInfo;

class IRHIAdapter;
class IRHIBarrier;
class IRHIBuffer;
class IRHICommandBuffer;
class IRHICommandPool;
class IRHICommandQueue;
class IRHIDevice;
class IRHIFence;
class IRHIHeap;
class IRHIInstance;
class IRHIModule;
class IRHISampler;
class IRHISemaphore;
class IRHIShader;
class IRHISwapChain;
class IRHITexture;

using AdapterHandle = RefCountPtr<IRHIAdapter>;
using BarrierHandle = RefCountPtr<IRHIBarrier>;
using BufferHandle = RefCountPtr<IRHIBuffer>;
using CommandBufferHandle = RefCountPtr<IRHICommandBuffer>;
using CommandPoolHandle = RefCountPtr<IRHICommandPool>;
using CommandQueueHandle = RefCountPtr<IRHICommandQueue>;
using DeviceHandle = RefCountPtr<IRHIDevice>;
using FenceHandle = RefCountPtr<IRHIFence>;
using HeapHandle = RefCountPtr<IRHIHeap>;
using InstanceHandle = RefCountPtr<IRHIInstance>;
using ModuleHandle = RefCountPtr<IRHIModule>;
using SamplerHandle = RefCountPtr<IRHISampler>;
using SemaphoreHandle = RefCountPtr<IRHISemaphore>;
using ShaderHandle = RefCountPtr<IRHIShader>;
using SwapChainHandle = RefCountPtr<IRHISwapChain>;
using TextureHandle = RefCountPtr<IRHITexture>;

}