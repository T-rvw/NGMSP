#include <Core/HAL/PlatformModule.h>

#include "PlatformImplTypes.h"

#include <Core/Base/TypeTraits.h>

namespace ow
{

PlatformModule::PlatformModule()
{
	m_pImpl = new PlatformModuleImpl();
}

PlatformModule::PlatformModule(const char* pModuleName, const char* pModulePath)
{
	m_pImpl = new PlatformModuleImpl();
	m_pImpl->SetModuleName(pModuleName);
	m_pImpl->SetModulePath(pModulePath);
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

const char* PlatformModule::GetModuleName() const
{
	return m_pImpl->GetModuleName();
}

void PlatformModule::SetModuleName(const char* pModuleName)
{
	m_pImpl->SetModuleName(pModuleName);
}

const char* PlatformModule::GetModulePath() const
{
	return m_pImpl->GetModulePath();
}

void PlatformModule::SetModulePath(const char* pModulePath)
{
	m_pImpl->SetModulePath(pModulePath);
}

bool PlatformModule::IsLoaded() const
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

void* PlatformModule::GetFunctionAddress(const char* pFuncName)
{
	return m_pImpl->GetFunctionAddress(pFuncName);
}

}