#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class PlatformModuleImpl;

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
	PlatformModule(PlatformModule&& other);
	PlatformModule& operator=(PlatformModule&& other);
	~PlatformModule();

	bool IsValid() const;
	void* GetHandle() const;

	bool Load(const char* pFilePath);
	void Unload();

private:
	PlatformModuleImpl* m_pImpl = nullptr;
};

}