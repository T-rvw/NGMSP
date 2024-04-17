#pragma once

#include <Core/HAL/APIDefinition.h>

#include <vector>

namespace ow
{

struct ModuleData;

class IRHICommandQueue;
class IRHIDevice;
class IRHIFence;
class IRHIInstance;
class IRHIModule;

struct RHIInstanceCreateInfo;

class GraphicsContext
{
public:
	RHI_API GraphicsContext() = default;
	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;
	GraphicsContext(GraphicsContext&&) = default;
	GraphicsContext& operator=(GraphicsContext&&) = default;
	RHI_API ~GraphicsContext();

	RHI_API void Initialize(const RHIInstanceCreateInfo& createInfo);

private:
	ModuleData* m_pRHILibrary = nullptr;
	IRHIModule* m_pRHIModule = nullptr;
	IRHIInstance* m_pRHIInstance = nullptr;
	IRHIDevice* m_pRHIDevice = nullptr;

	std::vector<IRHICommandQueue*> m_pRHICommandQueues;
	std::vector<IRHIFence*> m_pRHICommandQueueFences;
};

}