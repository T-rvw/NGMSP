#include <Core/Modules/ModuleManager.h>

#include "ModuleManagerImpl.h"

namespace ow
{

ModuleManager& ModuleManager::Get()
{
	static ModuleManager moduleManager;
	return moduleManager;
}

ModuleManager::ModuleManager()
{
	m_pImpl = new ModuleManagerImpl();
}

ModuleManager::ModuleManager(ModuleManager&& other) noexcept
{
	*this = MoveTemp(other);
}

ModuleManager& ModuleManager::operator=(ModuleManager&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

ModuleManager::~ModuleManager()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void ModuleManager::LoadModules()
{
	m_pImpl->LoadModules();
}

void ModuleManager::UnloadModules()
{
	m_pImpl->UnloadModules();
}

ModuleData* ModuleManager::AddModule(const char* pModuleName, const char* pModulePath)
{
	return m_pImpl->AddModule(pModuleName, pModulePath);
}

ModuleData* ModuleManager::LoadModule(const char* pModuleName, const char* pModulePath)
{
	return m_pImpl->LoadModule(pModuleName, pModulePath);
}

bool ModuleManager::FindModule(const char* pModuleName) const
{
	return m_pImpl->FindModule(pModuleName);
}

ModuleData* ModuleManager::GetModule(const char* pModuleName)
{
	return m_pImpl->GetModule(pModuleName);
}

const ModuleData* ModuleManager::GetModule(const char* pModuleName) const
{
	return m_pImpl->GetModule(pModuleName);
}

void ModuleManager::RemoveModule(const char* pModuleName)
{
	m_pImpl->RemoveModule(pModuleName);
}

}