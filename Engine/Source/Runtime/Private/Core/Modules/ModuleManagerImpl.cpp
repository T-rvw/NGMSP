#include "ModuleManagerImpl.h"

namespace ow
{

ModuleManagerImpl::~ModuleManagerImpl()
{
	UnloadModules();
}

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

ModuleData* ModuleManagerImpl::AddModule(const char* pModuleName, const char* pModulePath, bool autoLoad)
{
	auto itModule = m_allModules.find(pModuleName);
	if (itModule != m_allModules.end())
	{
		return &itModule->second;
	}

	ModuleData moduleData;
	moduleData.Library.SetModuleName(pModuleName);
	moduleData.Library.SetModulePath(pModulePath);
	if (autoLoad)
	{
		Assert(moduleData.Library.Load());
		moduleData.InitFunc = (InitializeModuleFunc)moduleData.Library.GetFunctionAddress("InitializeModule");
		Assert(moduleData.InitFunc);
	}
	m_allModules[pModuleName] = MoveTemp(moduleData);

	return &m_allModules[pModuleName];
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