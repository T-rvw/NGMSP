#include <RHI/RHISurface.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHISurface.h>

namespace ow
{

RHISurface::RHISurface() = default;

RHISurface::RHISurface(RHISurface&& other) noexcept
{
	*this = MoveTemp(other);
}

RHISurface& RHISurface::operator=(RHISurface&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHISurface::~RHISurface()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHISurface::Reset(std::unique_ptr<IRHISurface>&& impl)
{
	m_pImpl = impl.release();
}

void* RHISurface::GetHandle() const
{
	return m_pImpl->GetHandle();
}

}