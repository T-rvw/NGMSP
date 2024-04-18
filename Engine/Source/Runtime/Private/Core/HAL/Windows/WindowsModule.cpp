#include "WindowsModule.h"

#include <cassert>

namespace ow
{

bool WindowsModule::Load()
{
	assert(!m_module);
	m_module = ::LoadLibraryA(m_modulePath.c_str());
	return m_module != nullptr;
}

void WindowsModule::Unload()
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