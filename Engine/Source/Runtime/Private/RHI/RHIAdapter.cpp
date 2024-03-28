#include <RHI/RHIAdapter.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIAdapter.h>

namespace ow
{

RHIAdapter::RHIAdapter() = default;

RHIAdapter::RHIAdapter(RHIAdapter&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIAdapter& RHIAdapter::operator=(RHIAdapter&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIAdapter::~RHIAdapter()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIAdapter::Init(std::unique_ptr<IRHIAdapter> pImpl)
{
	assert(pImpl.get());
	assert(!m_pImpl);
	m_pImpl = pImpl.release();
}

void RHIAdapter::Dump()
{
	printf("[RHIAdapter] Name = %s\n", GetName());
	printf("\tType = %s\n", EnumName(GetType()).data());
	printf("\tVendor = %s\n", EnumName(GetVendor()).data());
	printf("\tMemory = %llu MB\n", GetVRAMSize() / (1024 * 1024));
}

GPUAdapterType RHIAdapter::GetType() const
{
	return m_pImpl->GetInfo().Type;
}

GPUVendor RHIAdapter::GetVendor() const
{
	return m_pImpl->GetInfo().Vendor;
}

uint64 RHIAdapter::GetVRAMSize() const
{
	return m_pImpl->GetInfo().VRAMSize;
}

const char* RHIAdapter::GetName() const
{
	return m_pImpl->GetInfo().Name.c_str();
}

}