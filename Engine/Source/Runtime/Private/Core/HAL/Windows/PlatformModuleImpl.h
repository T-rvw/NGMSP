#pragma once

#include "WindowsPlatform.h"

#include <string>

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

	void SetFilePath(const char* pFilePath);
	const char* GetFilePath() const;

	HMODULE GetHandle() const;
	bool Load();
	void Unload();

private:
	std::string m_filePath;
	HMODULE m_module;
};

}