#include "PlatformModuleImpl.h"

namespace ow
{

HMODULE PlatformModuleImpl::GetHandle() const
{
	return m_module;
}

bool PlatformModuleImpl::Load(const char* pFilePath)
{
	assert(!m_module);
	m_module = ::LoadLibraryA(pFilePath);
	return m_module != nullptr;
}

void PlatformModuleImpl::Unload()
{
	if (m_module != nullptr)
	{
		::FreeLibrary(m_module);
		m_module = nullptr;
	}
}

}