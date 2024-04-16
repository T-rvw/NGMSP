#include <Graphics/GraphicsContext.h>

#include <cassert>

namespace ow
{

GraphicsContext::~GraphicsContext() = default;

void GraphicsContext::InitializeInstance(const RHIInstanceCreateInfo& createInfo)
{
	switch (createInfo.Backend)
	{
	case RHIBackend::D3D12:
	{
		m_pRHILibrary = ModuleManager::Get().LoadModule("[RHI][D3D12]", "RHID3D12");
		break;
	}
	case RHIBackend::Vulkan:
	{
		m_pRHILibrary = ModuleManager::Get().LoadModule("[RHI][Vulkan]", "RHIVulkan");
		break;
	}
	default:
	{
		assert("Unknown RHI backend.");
		break;
	}
	}

	assert(m_pRHILibrary);
	m_pRHIModule = static_cast<IRHIModule*>(m_pRHILibrary->InitFunc());
	m_pRHIInstance = m_pRHIModule->CreateRHIInstance();
	assert(m_pRHIInstance);
	m_pRHIInstance->Init(createInfo);
}

}