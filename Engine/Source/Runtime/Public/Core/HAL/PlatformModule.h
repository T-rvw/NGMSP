#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IPlatformModule;

/// <summary>
/// Module means a dynamicly loading library, such as .dll in Windows.
/// It is useful to decouple subsystems in different types or implement features such as PluginsManager.
/// </summary>
class CORE_API PlatformModule
{
public:
	PlatformModule();
	explicit PlatformModule(const char* pModuleName, const char* pModulePath);
	PlatformModule(const PlatformModule&) = delete;
	PlatformModule& operator=(const PlatformModule&) = delete;
	PlatformModule(PlatformModule&& other) noexcept;
	PlatformModule& operator=(PlatformModule&& other) noexcept;
	~PlatformModule();

	const char* GetModuleName() const;
	void SetModuleName(const char* pModuleName);

	const char* GetModulePath() const;
	void SetModulePath(const char* pModulePath);

	bool IsLoaded() const;
	void* GetHandle() const;

	bool Load();
	void Unload();

	void* GetFunctionAddress(const char* pFuncName);

private:
	IPlatformModule* m_pImpl = nullptr;
};

}