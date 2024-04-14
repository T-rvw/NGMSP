#pragma once

#include <Core/Modules/ModuleManager.h>
#include <RHI/RHI.h>

class IRHIInstance;
class IRHIModule;
class ModuleData;

namespace ow
{

struct RHIInstanceCreateInfo;

class RHI_API GraphicsContext
{
public:
	GraphicsContext() = delete;
	explicit GraphicsContext(const RHIInstanceCreateInfo& createInfo);
	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;
	GraphicsContext(GraphicsContext&&) = default;
	GraphicsContext& operator=(GraphicsContext&&) = default;
	~GraphicsContext();

private:
	ModuleData* m_pRHILibrary = nullptr;
	IRHIModule* m_pRHIModule = nullptr;
	IRHIInstance* m_pRHIInstance = nullptr;
};

}