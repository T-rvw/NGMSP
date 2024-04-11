#include "ModuleManagerImpl.h"

namespace ow
{

void ModuleManagerImpl::LoadModules()
{
	for (auto& [_, module] : m_allModules)
	{
		if (!module.Library.IsLoaded())
		{
			module.Library.Load();
		}
	}
}

void ModuleManagerImpl::UnloadModules()
{
	for (auto& [_, module] : m_allModules)
	{
		if (module.Library.IsLoaded())
		{
			module.Library.Unload();
		}
	}
}

ModuleData* ModuleManagerImpl::AddModule(const char* pModuleName, const char* pModulePath)
{
	auto itModule = m_allModules.find(pModuleName);
	if (itModule != m_allModules.end())
	{
		return &itModule->second;
	}

	ModuleData module;
	module.Library.SetModuleName(pModuleName);
	module.Library.SetModulePath(pModulePath);
	m_allModules[pModuleName] = MoveTemp(module);
	return &m_allModules[pModuleName];
}

ModuleData* ModuleManagerImpl::LoadModule(const char* pModuleName, const char* pModulePath)
{
	auto* pModule = AddModule(pModuleName, pModulePath);
	assert(pModule->Library.Load());

	pModule->InitFunc = (InitializeModuleFunc)pModule->Library.GetFunctionAddress("InitializeModule");
	assert(pModule->InitFunc);
	return pModule;
}

bool ModuleManagerImpl::FindModule(const char* pModuleName) const
{
	return m_allModules.find(pModuleName) != m_allModules.end();
}

ModuleData* ModuleManagerImpl::GetModule(const char* pModuleName)
{
	auto itModule = m_allModules.find(pModuleName);
	return itModule != m_allModules.end() ? &itModule->second : nullptr;
}

void ModuleManagerImpl::RemoveModule(const char* pModuleName)
{
	if (auto itModule = m_allModules.find(pModuleName); itModule != m_allModules.end())
	{
		itModule->second.Library.Unload();
		m_allModules.erase(itModule);
	}
}

}