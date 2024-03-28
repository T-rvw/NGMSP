#pragma once

#include "WindowsHeader.hpp"

#include <Core/HAL/Interfaces/IPlatformApplication.h>

namespace ow
{

class WindowsApplication : public IPlatformApplication
{
public:
	static LRESULT CALLBACK WindowProcessFunc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

public:
	WindowsApplication() = default;
	WindowsApplication(const WindowsApplication&) = delete;
	WindowsApplication& operator=(const WindowsApplication&) = delete;
	WindowsApplication(WindowsApplication&&) = default;
	WindowsApplication& operator=(WindowsApplication&&) = default;
	~WindowsApplication() = default;

	virtual void Init() override;
	virtual void* GetProcessInstance() const override;
	virtual void Tick() override;

private:
	LRESULT WindowProcessFuncImpl(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);
	void RegisterWindowClass(HINSTANCE instance, HICON icon);
	void PumpMessages();
	double GetDeltaTime() const;

private:
	double m_currentTime;
	double m_lastTime;
};

}