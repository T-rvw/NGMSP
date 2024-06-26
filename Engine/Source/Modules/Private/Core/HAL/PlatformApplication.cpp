#include <Core/HAL/PlatformApplication.h>

#include "PlatformImplTypes.h"

#include <Core/Base/TypeTraits.h>

namespace ow
{

PlatformApplication::PlatformApplication()
{
	m_pImpl = new PlatformApplicationImpl();
}

PlatformApplication::PlatformApplication(PlatformApplication&& other)
{
	*this = MoveTemp(other);
}

PlatformApplication& PlatformApplication::operator=(PlatformApplication&& other)
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

bool PlatformApplication::PollMessages()
{
	return m_pImpl->PollMessages();
}

void* PlatformApplication::GetProcessInstance() const
{
	return m_pImpl->GetProcessInstance();
}

}