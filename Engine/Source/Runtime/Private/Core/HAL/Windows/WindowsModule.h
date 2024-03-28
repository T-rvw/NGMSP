#pragma once

#include "WindowsHeader.hpp"

#include <Core/HAL/Interfaces/IPlatformModule.h>

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

	virtual bool Init(const char* pFilePath) override;
	virtual void Free() override;

	virtual void* GetHandle() const override { return m_module; }
	virtual void* GetFunctionAddress(const char* pFuncName) override;

private:
	HMODULE m_module;
};

}