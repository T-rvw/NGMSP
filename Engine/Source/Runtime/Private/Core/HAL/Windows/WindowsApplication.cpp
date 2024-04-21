#include "WindowsApplication.h"

#include "WindowsWindow.h"

#include <Core/HAL/PlatformTime.h>

#include <cassert>

namespace ow
{

static WindowsApplication* s_pApplication = nullptr;
static HINSTANCE s_pProcessInstance = nullptr;

LRESULT CALLBACK WindowsApplication::WindowProcessFunc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
	return s_pApplication->WindowProcessFuncImpl(hwnd, msg, wParam, lParam);
}

WindowsApplication::WindowsApplication()
{
	assert(!s_pApplication);
	s_pApplication = this;
	s_pProcessInstance = ::GetModuleHandle(NULL);
	RegisterWindowClass(s_pProcessInstance, NULL);
}

void WindowsApplication::Init()
{
	PlatformTime::Init();
}

void WindowsApplication::Update()
{
	m_lastTime = m_currentTime;
	m_currentTime = PlatformTime::Seconds();

	while (PollMessages())
	{
	}
}

void WindowsApplication::Shutdown()
{
}

void* WindowsApplication::GetProcessInstance() const
{
	return s_pProcessInstance;
}

double WindowsApplication::GetDeltaTime() const
{
	return m_currentTime - m_lastTime;
}

bool WindowsApplication::PollMessages()
{
	MSG msg {};
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);

		if (WM_QUIT == msg.message)
		{
			return false;
		}
	}

	return true;
}

LRESULT WindowsApplication::WindowProcessFuncImpl(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			::PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

void WindowsApplication::RegisterWindowClass(HINSTANCE instance, HICON icon)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowsApplication::WindowProcessFunc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = WindowsWindow::WindowClassName;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	assert(::RegisterClassEx(&wc));
}

}