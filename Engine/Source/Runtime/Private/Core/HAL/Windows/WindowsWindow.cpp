#include "WindowsWindow.h"

#include <Core/HAL/PlatformTypes.h>

#include <cassert>

namespace ow
{

const TCHAR WindowsWindow::WindowClassName[] = TEXT("OW_WindowClass");

void WindowsWindow::Init(const WindowCreateInfo& createInfo, void* pInstance)
{
	HINSTANCE processInstance = pInstance ? (HINSTANCE)pInstance : ::GetModuleHandle(NULL);

	int32 windowWidth = createInfo.Width;
	int32 windowHeight = createInfo.Height;
	uint32 windowStyle = WS_OVERLAPPEDWINDOW;

	RECT windowRect = { 0, 0, windowWidth, windowHeight };
	::AdjustWindowRectEx(&windowRect, windowStyle, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	int32 windowLeft = (::GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	int32 windowTop = (::GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

	std::vector<TCHAR> title = CreateWideStringFromUTF8(createInfo.Title);
	m_handle = ::CreateWindowEx(NULL, WindowsWindow::WindowClassName, title.data(), windowStyle,
		windowLeft, windowTop,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		(HWND)createInfo.ParentWindow, NULL, (HINSTANCE)pInstance, NULL);
	assert(m_handle);

	::ShowWindow(m_handle, SW_SHOW);
	::SetFocus(m_handle);
}

}