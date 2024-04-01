#include <RHI/RHIDevice.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIDevice.h>

namespace ow
{

RHIDevice::RHIDevice() = default;

RHIDevice::RHIDevice(std::unique_ptr<IRHIDevice> impl)
{
	Init(MoveTemp(impl));
}

RHIDevice::RHIDevice(RHIDevice&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIDevice& RHIDevice::operator=(RHIDevice&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIDevice::~RHIDevice()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIDevice::Init(std::unique_ptr<IRHIDevice> impl)
{
	assert(impl.get());
	assert(!m_pImpl);
	m_pImpl = impl.release();
}

void* RHIDevice::GetHandle() const
{
	return m_pImpl->GetHandle();
}

}