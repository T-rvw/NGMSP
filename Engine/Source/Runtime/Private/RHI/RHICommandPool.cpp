#include <RHI/RHICommandPool.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHICommandPool.h>

namespace ow
{

RHICommandPool::RHICommandPool() = default;

RHICommandPool::RHICommandPool(RHICommandPool&& other) noexcept
{
	*this = MoveTemp(other);
}

RHICommandPool& RHICommandPool::operator=(RHICommandPool&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHICommandPool::~RHICommandPool()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHICommandPool::Init()
{
}

}