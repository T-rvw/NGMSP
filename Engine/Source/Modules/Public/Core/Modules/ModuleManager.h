#pragma once

#include <Core/Modules/IModule.h>

namespace ow
{

class ModuleManagerImpl;

class CORE_API ModuleManager final
{
public:
	static ModuleManager& Get();

public:
	ModuleManager();
	ModuleManager(const ModuleManager&) = delete;
	ModuleManager& operator=(const ModuleManager&) = delete;
	ModuleManager(ModuleManager&& other);
	ModuleManager& operator=(ModuleManager&& other);
	~ModuleManager();

	void LoadModules();
	void UnloadModules();

	ModuleData* AddModule(const char* pModuleName, const char* pModulePath, bool autoLoad = true);
	bool FindModule(const char* pModuleName) const;
	ModuleData* GetModule(const char* pModuleName);
	const ModuleData* GetModule(const char* pModuleName) const;
	void RemoveModule(const char* pModuleName);

private:
	ModuleManagerImpl* m_pImpl = nullptr;
};

}