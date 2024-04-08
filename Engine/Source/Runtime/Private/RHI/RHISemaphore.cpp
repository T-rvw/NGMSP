#include <RHI/RHISemaphore.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHISemaphore.h>

namespace ow
{

RHISemaphore::RHISemaphore() = default;

RHISemaphore::RHISemaphore(RHISemaphore&& other) noexcept
{
	*this = MoveTemp(other);
}

RHISemaphore& RHISemaphore::operator=(RHISemaphore&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHISemaphore::~RHISemaphore()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHISemaphore::Reset(std::unique_ptr<IRHISemaphore> impl)
{
	m_pImpl = impl.release();
}

}