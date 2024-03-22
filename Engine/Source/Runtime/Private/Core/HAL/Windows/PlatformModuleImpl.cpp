#include "PlatformModuleImpl.h"

namespace ow
{

void PlatformModuleImpl::SetFilePath(const char* pFilePath)
{
	m_filePath = pFilePath;
}

const char* PlatformModuleImpl::GetFilePath() const
{
	return m_filePath.c_str();
}

HMODULE PlatformModuleImpl::GetHandle() const
{
	return m_module;
}

bool PlatformModuleImpl::Load()
{
	if (m_filePath.empty())
	{
		return false;
	}

	m_module = ::LoadLibraryA(m_filePath.c_str());
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