#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/Base/RefCountPtr.h>
#include <Core/HAL/APIDefinition.h>
#include <RHI/RHIEnums.h>

#include <vector>

namespace ow
{

struct ModuleData;

class IRHICommandQueue;
class IRHIDevice;
class IRHIFence;
class IRHIInstance;
class IRHIModule;
class IRHISwapChain;

struct RHIInstanceCreateInfo;

struct GraphicsCreateInfo
{
	RHIBackend Backend = RHIBackend::Vulkan;
	BitFlags<RHIFeatures> Features;
	void* NativeInstanceHandle = nullptr;
	void* NativeWindowHandle = nullptr;
    uint32 BackBufferWidth = 1280;
    uint32 BackBufferHeight = 720;
};

class GraphicsContext
{
public:
	GFX_API GraphicsContext() = default;
	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;
	GFX_API GraphicsContext(GraphicsContext&&) = default;
	GFX_API GraphicsContext& operator=(GraphicsContext&&) = default;
	GFX_API ~GraphicsContext();

	GFX_API void Init(const GraphicsCreateInfo& createInfo);

private:
	RefCountPtr<IRHIModule> m_pRHIModule;
	RefCountPtr<IRHIInstance> m_pRHIInstance;
	RefCountPtr<IRHIDevice> m_pRHIDevice;
	RefCountPtr<IRHISwapChain> m_pRHISwapChain;
	std::vector<RefCountPtr<IRHICommandQueue>> m_rhiCommandQueues;
	std::vector<RefCountPtr<IRHIFence>> m_rhiCommandQueueFences;
};

}