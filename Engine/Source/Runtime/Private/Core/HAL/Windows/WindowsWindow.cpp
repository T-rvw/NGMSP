#include "WindowsWindow.h"

#include <Core/Base/Vector.h>
#include <Core/HAL/PlatformTypes.h>

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

	Vector<TCHAR> title = CreateWideStringFromUTF8(createInfo.Title);
	m_handle = ::CreateWindowEx(NULL, WindowsWindow::WindowClassName, title.data(), windowStyle,
		windowLeft, windowTop,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		(HWND)createInfo.ParentWindow, NULL, (HINSTANCE)pInstance, NULL);
	Assert(m_handle);

	::ShowWindow(m_handle, SW_SHOW);
	::SetFocus(m_handle);
}

Vector<char> WindowsWindow::GetTitle() const
{
	TCHAR title[128];
	::GetWindowText(m_handle, title, 64);
	return CreateUTF8StringFromWide(title);
}

uint32 WindowsWindow::GetWidth() const
{
	::RECT rect;
	::GetWindowRect(m_handle, &rect);
	return rect.right - rect.left;
}

uint32 WindowsWindow::GetHeight() const
{
	::RECT rect;
	::GetWindowRect(m_handle, &rect);
	return rect.bottom - rect.top;
}

}