#include <Core/HAL/PlatformProcess.h>

#include "PlatformImplTypes.h"

#include <Core/Base/TypeTraits.h>

namespace ow
{

PlatformProcess::PlatformProcess()
{
	m_pImpl = new PlatformProcessImpl();
}

PlatformProcess::PlatformProcess(PlatformProcess&& other) noexcept
{
	*this = MoveTemp(other);
}

PlatformProcess& PlatformProcess::operator=(PlatformProcess&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformProcess::~PlatformProcess()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

bool PlatformProcess::Init()
{
	return m_pImpl->Init();
}

}