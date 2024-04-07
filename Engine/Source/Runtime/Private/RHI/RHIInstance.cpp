#include <RHI/RHIInstance.h>

#include "D3D12/D3D12Instance.h"
#include "Vulkan/VulkanInstance.h"

#include <RHI/Interfaces/IRHIDevice.h>
#include <RHI/RHITypes.h>

namespace ow
{

RHIInstance RHIInstance::Create(const RHIInstanceCreateInfo& createInfo)
{
	RHIInstance instance;
	switch (createInfo.Backend)
	{
	case RHIBackend::D3D12:
	{
		instance.m_pImpl = new D3D12Instance();
		break;
	}
	case RHIBackend::Vulkan:
	{
		instance.m_pImpl = new VulkanInstance();
		break;
	}
	}

	instance.m_pImpl->Init(createInfo);
	return instance;
}

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

void RHIInstance::Init()
{
}

void RHIInstance::Dump()
{
	printf("[RHIInstance] Handle = %llu\n", reinterpret_cast<uint64>(GetHandle()));
	printf("\tBackend = %s\n", EnumName(GetBackend()).data());
}

RHIBackend RHIInstance::GetBackend() const
{
	return m_pImpl->GetBackend();
}

void* RHIInstance::GetHandle() const
{
	return m_pImpl->GetHandle();
}

std::vector<RHIAdapter> RHIInstance::EnumerateAdapters() const
{
	return m_pImpl->EnumerateAdapters();
}

}