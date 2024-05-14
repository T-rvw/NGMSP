#pragma once

#include <Core/Base/RefCountPtr.h>
#include <RHI/RHIEnums.h>

namespace ow
{

struct RHIAccelerationStructureCreateInfo;
struct RHIBarrierCreateInfo;
struct RHIBufferCreateInfo;
struct RHICommandListCreateInfo;
struct RHICommandPoolCreateInfo;
struct RHICommandQueueCreateInfo;
struct RHIDeviceCreateInfo;
struct RHIFenceCreateInfo;
struct RHIInstanceCreateInfo;
struct RHIPipelineLayoutCreateInfo;
struct RHIComputePipelineStateCreateInfo;
struct RHIGraphicsPipelineStateCreateInfo;
struct RHIRaytracingPipelineStateCreateInfo;
struct RHISamplerCreateInfo;
struct RHISemaphoreCreateInfo;
struct RHIShaderCreateInfo;
struct RHISwapChainCreateInfo;
struct RHITextureCreateInfo;

class IRHIAccelerationStructure;
class IRHIAdapter;
class IRHIBarrier;
class IRHIBuffer;
class IRHICommandList;
class IRHICommandPool;
class IRHICommandQueue;
class IRHIDevice;
class IRHIFence;
class IRHIHeap;
class IRHIInstance;
class IRHIModule;
class IRHIPipelineLayout;
class IRHIPipelineState;
class IRHISampler;
class IRHISemaphore;
class IRHIShader;
class IRHISwapChain;
class IRHITexture;

using AccelerationStructureHandle = RefCountPtr<IRHIAccelerationStructure>;
using AdapterHandle = RefCountPtr<IRHIAdapter>;
using BarrierHandle = RefCountPtr<IRHIBarrier>;
using BufferHandle = RefCountPtr<IRHIBuffer>;
using CommandListHandle = RefCountPtr<IRHICommandList>;
using CommandPoolHandle = RefCountPtr<IRHICommandPool>;
using CommandQueueHandle = RefCountPtr<IRHICommandQueue>;
using DeviceHandle = RefCountPtr<IRHIDevice>;
using FenceHandle = RefCountPtr<IRHIFence>;
using HeapHandle = RefCountPtr<IRHIHeap>;
using InstanceHandle = RefCountPtr<IRHIInstance>;
using PipelineLayoutHandle = RefCountPtr<IRHIPipelineLayout>;
using PipelineStateHandle = RefCountPtr<IRHIPipelineState>;
using RHIModuleHandle = RefCountPtr<IRHIModule>;
using SamplerHandle = RefCountPtr<IRHISampler>;
using SemaphoreHandle = RefCountPtr<IRHISemaphore>;
using ShaderHandle = RefCountPtr<IRHIShader>;
using SwapChainHandle = RefCountPtr<IRHISwapChain>;
using TextureHandle = RefCountPtr<IRHITexture>;

}