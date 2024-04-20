#pragma once

#include "WindowsHeader.h"

#include <Core/HAL/Interfaces/IPlatformModule.h>

#include <string>

namespace ow
{

class WindowsModule : public IPlatformModule
{
public:
	WindowsModule() = default;
	WindowsModule(const WindowsModule&) = delete;
	WindowsModule& operator=(const WindowsModule&) = delete;
	WindowsModule(WindowsModule&&) = default;
	WindowsModule& operator=(WindowsModule&&) = default;
	~WindowsModule() = default;

	virtual const char* GetModuleName() const override { return m_moduleName.c_str(); }
	virtual void SetModuleName(const char* pModuleName) override { m_moduleName = pModuleName; }

	virtual const char* GetModulePath() const override { return m_modulePath.c_str(); }
	virtual void SetModulePath(const char* pModulePath) override { m_modulePath = pModulePath; }

	virtual bool Load() override;
	virtual void Unload() override;

	virtual void* GetHandle() const override { return m_module; }
	virtual void* GetFunctionAddress(const char* pFuncName) override;

private:
	std::string m_moduleName;
	std::string m_modulePath;
	HMODULE m_module = nullptr;
};

}