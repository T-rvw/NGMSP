#include <Core/HAL/PlatformApplication.h>
#include <Core/HAL/Template.h>

#include "PlatformApplicationImpl.h"

namespace ow
{

PlatformApplication::PlatformApplication() = default;

PlatformApplication::PlatformApplication(PlatformApplication&& other) noexcept
{
	*this = MoveTemp(other);
}

PlatformApplication& PlatformApplication::operator=(PlatformApplication&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformApplication::~PlatformApplication()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

}