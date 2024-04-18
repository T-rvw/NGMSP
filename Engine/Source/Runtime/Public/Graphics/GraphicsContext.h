#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/HAL/APIDefinition.h>
#include <Core/HAL/BasicTypes.h>
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

	GFX_API void Initialize(const GraphicsCreateInfo& createInfo);

private:
	ModuleData* m_pRHILibrary = nullptr;
	IRHIModule* m_pRHIModule = nullptr;
	IRHIInstance* m_pRHIInstance = nullptr;
	IRHIDevice* m_pRHIDevice = nullptr;
	IRHISwapChain* m_pRHISwapChain = nullptr;

	std::vector<IRHICommandQueue*> m_pRHICommandQueues;
	std::vector<IRHIFence*> m_pRHICommandQueueFences;
};

}