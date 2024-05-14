#pragma once

#include "WindowsHeader.h"

#include <Core/HAL/Interfaces/IPlatformApplication.h>

namespace ow
{

class WindowsApplication : public IPlatformApplication
{
public:
	static LRESULT CALLBACK WindowProcessFunc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

public:
	WindowsApplication();
	WindowsApplication(const WindowsApplication&) = delete;
	WindowsApplication& operator=(const WindowsApplication&) = delete;
	WindowsApplication(WindowsApplication&&) = default;
	WindowsApplication& operator=(WindowsApplication&&) = default;
	virtual ~WindowsApplication() = default;

	virtual bool PollMessages() override;
	virtual void* GetProcessInstance() const override;
	
private:
	LRESULT WindowProcessFuncImpl(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);
	void RegisterWindowClass(HINSTANCE instance, HICON icon);

private:
	HINSTANCE m_instance;
};

}