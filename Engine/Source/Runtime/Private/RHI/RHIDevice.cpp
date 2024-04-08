#include <RHI/RHIDevice.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIDevice.h>
#include <RHI/RHICommandQueue.h>
#include <RHI/RHIFence.h>

namespace ow
{

RHIDevice::RHIDevice() = default;

RHIDevice::RHIDevice(std::unique_ptr<IRHIDevice> impl)
{
	Reset(MoveTemp(impl));
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

void RHIDevice::Reset(std::unique_ptr<IRHIDevice> impl)
{
	m_pImpl = impl.release();
}

void RHIDevice::Dump() const
{
	printf("[RHIDevice] Handle = %llu\n", reinterpret_cast<uint64>(GetHandle()));
}

void* RHIDevice::GetHandle() const
{
	return m_pImpl->GetHandle();
}

RHICommandQueue RHIDevice::CreateCommandQueue(const RHICommandQueueCreateInfo& commandQueueCI) const
{
	return m_pImpl->CreateCommandQueue(commandQueueCI);
}

RHIFence RHIDevice::CreateFence() const
{
	return m_pImpl->CreateFence();
}

}