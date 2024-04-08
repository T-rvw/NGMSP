#include <RHI/RHIBarrier.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIBarrier.h>

namespace ow
{

RHIBarrier::RHIBarrier() = default;

RHIBarrier::RHIBarrier(RHIBarrier&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIBarrier& RHIBarrier::operator=(RHIBarrier&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIBarrier::~RHIBarrier()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIBarrier::Reset(std::unique_ptr<IRHIBarrier> impl)
{
	m_pImpl = impl.release();
}

}