#include <RHI/RHIAdapter.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIAdapter.h>

namespace ow
{

RHIAdapter::RHIAdapter() = default;

RHIAdapter::RHIAdapter(std::unique_ptr<IRHIAdapter> impl)
{
	Init(MoveTemp(impl));
}

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

void RHIAdapter::Init(std::unique_ptr<IRHIAdapter> impl)
{
	assert(impl.get());
	assert(!m_pImpl);
	m_pImpl = impl.release();
}

void RHIAdapter::Dump()
{
	printf("[RHIAdapter] Name = %s\n", GetName());
	printf("\tType = %s\n", EnumName(GetType()).data());
	printf("\tVendor = %s\n", EnumName(GetVendor()).data());
	printf("\tVideo Memory = %llu MB\n", GetVideoMemorySize() >> 20);
	printf("\tSystem Memory = %llu MB\n", GetSystemMemorySize() >> 20);
	printf("\tShared Memory = %llu MB\n", GetSharedMemorySize() >> 20);
}

GPUAdapterType RHIAdapter::GetType() const
{
	return m_pImpl->GetInfo().Type;
}

GPUVendor RHIAdapter::GetVendor() const
{
	return m_pImpl->GetInfo().Vendor;
}

uint64 RHIAdapter::GetVideoMemorySize() const
{
	return m_pImpl->GetInfo().VideoMemorySize;
}

uint64 RHIAdapter::GetSystemMemorySize() const
{
	return m_pImpl->GetInfo().SystemMemorySize;
}

uint64 RHIAdapter::GetSharedMemorySize() const
{
	return m_pImpl->GetInfo().SharedMemorySize;
}

const char* RHIAdapter::GetName() const
{
	return m_pImpl->GetInfo().Name.c_str();
}

std::unique_ptr<RHIDevice> RHIAdapter::CreateDevice(const RHIDeviceCreateInfo& createInfo) const
{
	return m_pImpl->CreateDevice(createInfo);
}

}