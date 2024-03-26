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

	bool Init(const char* pFilePath);
	void Free();

	void* GetFunctionAddress(const char* pFuncName);

private:
	PlatformModuleImpl* m_pImpl = nullptr;
};

// Helper macro to load apis dynamically with assert
#define LOAD_MODULE_API(Module, API)                          \
        do                                                    \
        {                                                     \
            API = (API##Func)Module.GetFunctionAddress(#API); \
			assert(API);									  \
        } while (false)

}