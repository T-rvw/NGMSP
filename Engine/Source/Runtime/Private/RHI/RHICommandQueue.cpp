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

void RHICommandQueue::Reset(std::unique_ptr<IRHICommandQueue> impl)
{
	m_pImpl = impl.release();
}

void RHICommandQueue::Dump() const
{
	printf("[RHICommandQueue] Handle = %llu\n", reinterpret_cast<uint64>(GetHandle()));
}

void* RHICommandQueue::GetHandle() const
{
	return m_pImpl->GetHandle();
}

void RHICommandQueue::SetType(RHICommandType commandQueueType)
{
	m_pImpl->SetType(commandQueueType);
}

RHICommandType RHICommandQueue::GetType() const
{
	return m_pImpl->GetType();
}

}