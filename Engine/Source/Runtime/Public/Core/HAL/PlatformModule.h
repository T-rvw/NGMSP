#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IPlatformModule;

/// <summary>
/// Module means a dynamicly loading library, such as .dll in Windows.
/// It is useful to decouple subsystems in different types or implement features such as PluginsManager.
/// </summary>
class ENGINE_API PlatformModule
{
public:
	PlatformModule();
	PlatformModule(const PlatformModule&) = delete;
	PlatformModule& operator=(const PlatformModule&) = delete;
	PlatformModule(PlatformModule&& other) noexcept;
	PlatformModule& operator=(PlatformModule&& other) noexcept;
	~PlatformModule();

	bool IsValid() const;
	void* GetHandle() const;

	bool Init(const char* pFilePath);
	void Free();

	void* GetFunctionAddress(const char* pFuncName);

private:
	IPlatformModule* m_pImpl = nullptr;
};

}