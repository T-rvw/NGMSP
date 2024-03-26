#include <Core/HAL/PlatformTime.h>

#include "PlatformApplicationImpl.h"
#include "PlatformWindowImpl.h"

namespace ow
{

static PlatformApplicationImpl* s_pApplication = nullptr;
static HINSTANCE s_pProcessInstance = nullptr;

LRESULT CALLBACK PlatformApplicationImpl::WindowProcessFunc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
	return s_pApplication->WindowProcessFuncImpl(hwnd, msg, wParam, lParam);
}

void PlatformApplicationImpl::Init(void* pInstance, void* pIcon)
{
	assert(!s_pApplication);
	s_pApplication = this;
	s_pProcessInstance = (HINSTANCE)pInstance;
	PlatformTime::Init();
	RegisterWindowClass(s_pProcessInstance, (HICON)pIcon);
}

HINSTANCE PlatformApplicationImpl::GetProcessInstance() const
{
	return s_pProcessInstance;
}

double PlatformApplicationImpl::GetDeltaTime() const
{
	return m_currentTime - m_lastTime;
}

void PlatformApplicationImpl::Tick()
{
	m_lastTime = m_currentTime;
	m_currentTime = PlatformTime::Seconds();

	MSG msg {};
	while (msg.message != WM_QUIT)
	{
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

LRESULT PlatformApplicationImpl::WindowProcessFuncImpl(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

void PlatformApplicationImpl::RegisterWindowClass(HINSTANCE instance, HICON icon)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = PlatformApplicationImpl::WindowProcessFunc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = PlatformWindowImpl::WindowClassName;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	assert(::RegisterClassEx(&wc));
}

}