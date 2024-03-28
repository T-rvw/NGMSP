#include "WindowsModule.h"

namespace ow
{

bool WindowsModule::Init(const char* pFilePath)
{
	assert(!m_module);
	m_module = ::LoadLibraryA(pFilePath);
	return m_module != nullptr;
}

void WindowsModule::Free()
{
	if (m_module != nullptr)
	{
		::FreeLibrary(m_module);
		m_module = nullptr;
	}
}

void* WindowsModule::GetFunctionAddress(const char* pFuncName)
{
	assert(m_module);
	return ::GetProcAddress(m_module, pFuncName);
}

}