#include <RHI/RHICommandBuffer.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHICommandBuffer.h>

namespace ow
{

RHICommandBuffer::RHICommandBuffer() = default;

RHICommandBuffer::RHICommandBuffer(RHICommandBuffer&& other) noexcept
{
	*this = MoveTemp(other);
}

RHICommandBuffer& RHICommandBuffer::operator=(RHICommandBuffer&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHICommandBuffer::~RHICommandBuffer()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHICommandBuffer::Init()
{
}

}