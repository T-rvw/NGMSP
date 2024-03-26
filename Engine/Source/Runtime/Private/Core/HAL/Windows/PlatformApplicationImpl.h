#pragma once

#include <Core/HAL/Platform/Windows/WindowsPlatform.h>

namespace ow
{

class PlatformApplicationImpl
{
public:
	static LRESULT CALLBACK WindowProcessFunc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

public:
	PlatformApplicationImpl() = default;
	PlatformApplicationImpl(const PlatformApplicationImpl&) = delete;
	PlatformApplicationImpl& operator=(const PlatformApplicationImpl&) = delete;
	PlatformApplicationImpl(PlatformApplicationImpl&&) = default;
	PlatformApplicationImpl& operator=(PlatformApplicationImpl&&) = default;
	~PlatformApplicationImpl() = default;

	void Init(void* pInstance, void* pIcon);
	HINSTANCE GetProcessInstance() const;

	double GetDeltaTime() const;
	void Tick();

private:
	LRESULT WindowProcessFuncImpl(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);
	void RegisterWindowClass(HINSTANCE instance, HICON icon);
	void PumpMessages();

private:
	double m_currentTime;
	double m_lastTime;
};

}