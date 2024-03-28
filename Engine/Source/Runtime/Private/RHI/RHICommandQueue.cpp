#include <RHI/RHICommandQueue.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHICommandQueue.h>

namespace ow
{

RHICommandQueue::RHICommandQueue() = default;

RHICommandQueue::RHICommandQueue(RHICommandQueue&& other) noexcept
{
	*this = MoveTemp(other);
}

RHICommandQueue& RHICommandQueue::operator=(RHICommandQueue&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHICommandQueue::~RHICommandQueue()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHICommandQueue::Init()
{
}

}