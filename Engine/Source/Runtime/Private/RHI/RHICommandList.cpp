#include <RHI/RHICommandList.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHICommandList.h>

namespace ow
{

RHICommandList::RHICommandList() = default;

RHICommandList::RHICommandList(RHICommandList&& other) noexcept
{
	*this = MoveTemp(other);
}

RHICommandList& RHICommandList::operator=(RHICommandList&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHICommandList::~RHICommandList()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHICommandList::Init()
{
}

}