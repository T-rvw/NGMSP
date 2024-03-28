#include <RHI/RHIInstance.h>

#include "D3D12/D3D12Instance.h"
#include "Vulkan/VulkanInstance.h"

#include <RHI/Interfaces/IRHIDevice.h>
#include <RHI/RHITypes.h>

namespace ow
{

RHIInstance::RHIInstance() = default;

RHIInstance::RHIInstance(RHIInstance&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIInstance& RHIInstance::operator=(RHIInstance&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIInstance::~RHIInstance()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIInstance::Init(const RHIInstanceCreateInfo& createInfo)
{
	switch (createInfo.Backend)
	{
	case RHIBackend::D3D12:
	{
		m_pImpl = new D3D12Instance();
		break;
	}
	case RHIBackend::Vulkan:
	{
		m_pImpl = new VulkanInstance();
		break;
	}
	}

	m_pImpl->Init(createInfo);
}

void* RHIInstance::GetHandle() const
{
	return m_pImpl->GetHandle();
}

std::vector<std::unique_ptr<RHIAdapter>> RHIInstance::EnumAdapters()
{
	return m_pImpl->EnumAdapters();
}

}