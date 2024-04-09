#include <RHI/RHISwapChain.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHISwapChain.h>

namespace ow
{

RHISwapChain::RHISwapChain() = default;

RHISwapChain::RHISwapChain(RHISwapChain&& other) noexcept
{
	*this = MoveTemp(other);
}

RHISwapChain& RHISwapChain::operator=(RHISwapChain&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHISwapChain::~RHISwapChain()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHISwapChain::Reset(std::unique_ptr<IRHISwapChain>&& impl)
{
	m_pImpl = impl.release();
}

}