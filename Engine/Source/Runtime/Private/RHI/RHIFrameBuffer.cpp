#include <RHI/RHIFramebuffer.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIFramebuffer.h>

namespace ow
{

RHIFramebuffer::RHIFramebuffer() = default;

RHIFramebuffer::RHIFramebuffer(RHIFramebuffer&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIFramebuffer& RHIFramebuffer::operator=(RHIFramebuffer&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIFramebuffer::~RHIFramebuffer()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIFramebuffer::Reset(std::unique_ptr<IRHIFramebuffer>&& impl)
{
	m_pImpl = impl.release();
}

}