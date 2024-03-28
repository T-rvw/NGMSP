#include <RHI/RHIBuffer.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIBuffer.h>

namespace ow
{

RHIBuffer::RHIBuffer() = default;

RHIBuffer::RHIBuffer(RHIBuffer&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIBuffer& RHIBuffer::operator=(RHIBuffer&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIBuffer::~RHIBuffer()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIBuffer::Init()
{
}

}