#include <Core/HAL/PlatformModule.h>

#include "PlatformModuleImpl.h"

namespace ow
{

PlatformModule::PlatformModule()
{
	m_pImpl = new PlatformModuleImpl();
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

bool PlatformModule::Init(const char* pFilePath)
{
	return m_pImpl->Init(pFilePath);
}

void PlatformModule::Free()
{
	m_pImpl->Free();
}

void* PlatformModule::GetFunctionAddress(const char* pFuncName)
{
	return m_pImpl->GetFunctionAddress(pFuncName);
}

}