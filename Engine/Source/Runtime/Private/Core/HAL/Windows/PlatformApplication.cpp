#include <Core/HAL/PlatformApplication.h>

#include "PlatformApplicationImpl.h"

namespace ow
{

PlatformApplication::PlatformApplication()
{
	m_pImpl = new PlatformApplicationImpl();
}

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

void PlatformApplication::Init(void* pInstance, void* pIcon)
{
	m_pImpl->Init(pInstance, pIcon);
}

void* PlatformApplication::GetProcessInstance() const
{
	return m_pImpl->GetProcessInstance();
}

void PlatformApplication::Run()
{
	m_pImpl->Tick();
}

}