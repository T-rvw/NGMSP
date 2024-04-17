#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

struct ModuleData;

class IRHIInstance;
class IRHIModule;

struct RHIInstanceCreateInfo;

class RHI_API GraphicsContext
{
public:
	GraphicsContext() = default;
	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;
	GraphicsContext(GraphicsContext&&) = default;
	GraphicsContext& operator=(GraphicsContext&&) = default;
	~GraphicsContext();

	void InitializeInstance(const RHIInstanceCreateInfo& createInfo);

private:
	ModuleData* m_pRHILibrary = nullptr;
	IRHIModule* m_pRHIModule = nullptr;
	IRHIInstance* m_pRHIInstance = nullptr;
};

}