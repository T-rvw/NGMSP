#include <Core/HAL/PlatformSemaphore.h>

#include "PlatformImplTypes.h"

#include <Core/Base/TypeTraits.h>

namespace ow
{

PlatformSemaphore::PlatformSemaphore()
{
	m_pImpl = new PlatformSemaphoreImpl();
}

PlatformSemaphore::PlatformSemaphore(PlatformSemaphore&& other) noexcept
{
	*this = MoveTemp(other);
}

PlatformSemaphore& PlatformSemaphore::operator=(PlatformSemaphore&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformSemaphore::~PlatformSemaphore()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void PlatformSemaphore::Init(int32 initialCount, int32 maxCount)
{
	m_pImpl->Init(initialCount, maxCount);
}

void PlatformSemaphore::Wait() const
{
	m_pImpl->Wait();
}

void PlatformSemaphore::Signal(int32 releaseCount) const
{
	m_pImpl->Signal(releaseCount);
}

}