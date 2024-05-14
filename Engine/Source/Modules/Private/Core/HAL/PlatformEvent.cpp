#include <Core/HAL/PlatformEvent.h>

#include "PlatformImplTypes.h"

#include <Core/Base/TypeTraits.h>

namespace ow
{

PlatformEvent::PlatformEvent()
{
	m_pImpl = new PlatformEventImpl();
}

PlatformEvent::PlatformEvent(PlatformEvent&& other)
{
	*this = MoveTemp(other);
}

PlatformEvent& PlatformEvent::operator=(PlatformEvent&& other)
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformEvent::~PlatformEvent()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void PlatformEvent::Init(const char* pName)
{
	m_pImpl->Init(pName);
}

void PlatformEvent::Shutdown()
{
	m_pImpl->Shutdown();
}

bool PlatformEvent::IsValid() const
{
	return GetHandle() != nullptr;
}

void* PlatformEvent::GetHandle() const
{
	return m_pImpl->GetHandle();
}

void PlatformEvent::Signal()
{
	m_pImpl->Signal();
}

void PlatformEvent::Wait()
{
	m_pImpl->Wait();
}

}