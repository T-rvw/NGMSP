#include <RHI/RHIFence.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIFence.h>

namespace ow
{

RHIFence::RHIFence() = default;

RHIFence::RHIFence(RHIFence&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIFence& RHIFence::operator=(RHIFence&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIFence::~RHIFence()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIFence::Reset(std::unique_ptr<IRHIFence>&& impl)
{
	m_pImpl = impl.release();
}

}