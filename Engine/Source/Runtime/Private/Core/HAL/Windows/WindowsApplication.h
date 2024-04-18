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
	WindowsApplication();
	WindowsApplication(const WindowsApplication&) = delete;
	WindowsApplication& operator=(const WindowsApplication&) = delete;
	WindowsApplication(WindowsApplication&&) = default;
	WindowsApplication& operator=(WindowsApplication&&) = default;
	~WindowsApplication() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void* GetProcessInstance() const override;
	
private:
	bool PollMessages();
	LRESULT WindowProcessFuncImpl(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);
	void RegisterWindowClass(HINSTANCE instance, HICON icon);
	double GetDeltaTime() const;

private:
	double m_currentTime;
	double m_lastTime;
};

}