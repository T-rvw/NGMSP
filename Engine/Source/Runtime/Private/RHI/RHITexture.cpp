#include <RHI/RHITexture.h>

#include <Core/HAL/Platform.h>
#include <RHI/Interfaces/IRHITexture.h>

namespace ow
{

RHITexture::RHITexture() = default;

RHITexture::RHITexture(RHITexture&& other) noexcept
{
	*this = MoveTemp(other);
}

RHITexture& RHITexture::operator=(RHITexture&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

RHITexture::~RHITexture()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void RHITexture::Reset(std::unique_ptr<IRHITexture>&& pImpl)
{
	m_pImpl = pImpl.release();
}

}