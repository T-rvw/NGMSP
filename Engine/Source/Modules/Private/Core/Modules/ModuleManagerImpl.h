#pragma once

#include <Core/Base/TypeTraits.h>
#include <Core/Containers/Map.h>
#include <Core/Modules/IModule.h>
#include <Core/String/String.h>

namespace ow
{

class ModuleManagerImpl
{
public:
	ModuleManagerImpl() = default;
	ModuleManagerImpl(const ModuleManagerImpl&) = delete;
	ModuleManagerImpl& operator=(const ModuleManagerImpl&) = delete;
	ModuleManagerImpl(ModuleManagerImpl&&) = default;
	ModuleManagerImpl& operator=(ModuleManagerImpl&&) = default;
	~ModuleManagerImpl();

	void LoadModules();
	void UnloadModules();

	ModuleData* AddModule(const char* pModuleName, const char* pModulePath, bool autoLoad);
	bool FindModule(const char* pModuleName) const;
	ModuleData* GetModule(const char* pModuleName);
	const ModuleData* GetModule(const char* pModuleName) const { return GetModule(pModuleName); }
	void RemoveModule(const char* pModuleName);

private:
	Map<String, ModuleData> m_allModules;
};

}