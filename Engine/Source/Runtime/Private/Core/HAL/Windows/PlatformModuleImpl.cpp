#include "PlatformModuleImpl.h"

namespace ow
{

HMODULE PlatformModuleImpl::GetHandle() const
{
	return m_module;
}

bool PlatformModuleImpl::Init(const char* pFilePath)
{
	assert(!m_module);
	m_module = ::LoadLibraryA(pFilePath);
	return m_module != nullptr;
}

void PlatformModuleImpl::Free()
{
	if (m_module != nullptr)
	{
		::FreeLibrary(m_module);
		m_module = nullptr;
	}
}

void* PlatformModuleImpl::GetFunctionAddress(const char* pFuncName)
{
	assert(m_module);
	return ::GetProcAddress(m_module, pFuncName);
}

}