#pragma once

#include "WindowsHeader.hpp"
#include "../IPlatformWindow.h"

namespace ow
{

struct WindowCreateInfo;

class WindowsWindow : public IPlatformWindow
{
public:
	static const TCHAR WindowClassName[];

public:
	WindowsWindow() = default;
	WindowsWindow(const WindowsWindow&) = delete;
	WindowsWindow& operator=(const WindowsWindow&) = delete;
	WindowsWindow(WindowsWindow&&) = default;
	WindowsWindow& operator=(WindowsWindow&&) = default;
	~WindowsWindow() = default;

	virtual void Init(const WindowCreateInfo& createInfo, void* pInstance) override;
	virtual void* GetHandle() const override;

private:
	HWND m_handle;
};

}