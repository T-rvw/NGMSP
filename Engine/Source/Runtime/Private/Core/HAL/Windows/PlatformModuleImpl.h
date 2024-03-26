#pragma once

#include <Core/HAL/Platform/Windows/WindowsPlatform.h>

namespace ow
{

class PlatformModuleImpl
{
public:
	PlatformModuleImpl() = default;
	PlatformModuleImpl(const PlatformModuleImpl&) = delete;
	PlatformModuleImpl& operator=(const PlatformModuleImpl&) = delete;
	PlatformModuleImpl(PlatformModuleImpl&&) = default;
	PlatformModuleImpl& operator=(PlatformModuleImpl&&) = default;
	~PlatformModuleImpl() = default;

	HMODULE GetHandle() const;
	bool Load(const char* pFilePath);
	void Unload();

private:
	HMODULE m_module;
};

}