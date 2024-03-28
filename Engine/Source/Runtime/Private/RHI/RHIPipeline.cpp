#include <RHI/RHIPipeline.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHIPipeline.h>

namespace ow
{

RHIPipeline::RHIPipeline() = default;

RHIPipeline::RHIPipeline(RHIPipeline&& other) noexcept
{
	*this = MoveTemp(other);
}

RHIPipeline& RHIPipeline::operator=(RHIPipeline&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHIPipeline::~RHIPipeline()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHIPipeline::Init()
{
}

}