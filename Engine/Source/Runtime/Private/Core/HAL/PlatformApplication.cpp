#include <Core/HAL/PlatformApplication.h>

#include "PlatformImplTypes.h"

#include <Core/Base/TypeTraits.h>
#include <Core/HAL/Interfaces/IApplication.h>

namespace ow
{

PlatformApplication::PlatformApplication(IApplication* pApplication) :
	m_pApplication(pApplication)
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

void* PlatformApplication::GetProcessInstance() const
{
	return m_pImpl->GetProcessInstance();
}

void PlatformApplication::Run()
{
	m_pImpl->Init();
	m_pApplication->Init();

	while (m_pImpl->ShouldQuit())
	{
		m_pImpl->Update();
		m_pApplication->Update();
	}

	m_pApplication->Shutdown();
	m_pImpl->Shutdown();
}

}