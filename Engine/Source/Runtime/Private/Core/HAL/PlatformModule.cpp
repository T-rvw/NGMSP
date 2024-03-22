#include <Core/HAL/PlatformModule.h>
#include <Core/HAL/Template.h>

#if defined(PLATFORM_ANDROID)
#include "Android/PlatformModuleImpl.h"
#elif defined(PLATFORM_IOS)
#include "IOS/PlatformModuleImpl.h"
#elif defined(PLATFORM_LINUX)
#include "Linux/PlatformModuleImpl.h"
#elif defined(PLATFORM_MAC)
#include "Mac/PlatformModuleImpl.h"
#elif defined(PLATFORM_WINDOWS)
#include "Windows/PlatformModuleImpl.h"
#endif

namespace ow
{

PlatformModule::PlatformModule() = default;

PlatformModule::PlatformModule(const char* pModuleFilePath)
{
	m_pImpl = new PlatformModuleImpl();
	m_pImpl->SetFilePath(pModuleFilePath);
}

PlatformModule::PlatformModule(PlatformModule&& other)
{
	*this = MoveTemp(other);
}

PlatformModule& PlatformModule::operator=(PlatformModule&& other)
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformModule::~PlatformModule()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

bool PlatformModule::IsValid() const
{
	return m_pImpl->GetHandle() != nullptr;
}

void* PlatformModule::GetHandle() const
{
	return m_pImpl->GetHandle();
}

bool PlatformModule::Load()
{
	return m_pImpl->Load();
}

void PlatformModule::Unload()
{
	m_pImpl->Unload();
}

}