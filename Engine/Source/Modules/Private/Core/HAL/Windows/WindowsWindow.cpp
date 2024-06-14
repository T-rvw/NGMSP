#include "WindowsWindow.h"

#include <Core/Containers/Vector.h>
#include <Core/HAL/PlatformTypes.h>

namespace ow
{

const TCHAR WindowsWindow::WindowClassName[] = TEXT("OW_WindowClass");

void WindowsWindow::Init(const WindowCreateInfo& createInfo, void* pInstance)
{
	HINSTANCE processInstance = pInstance ? (HINSTANCE)pInstance : ::GetModuleHandle(NULL);

	uint32 windowStyle = WS_OVERLAPPEDWINDOW;
	const auto& rectInfo = createInfo.WindowRect;
	RECT windowRect = { 0, 0, static_cast<LONG>(rectInfo.GetRight()), static_cast<LONG>(rectInfo.GetBottom()) };
	::AdjustWindowRect(&windowRect, windowStyle, false);

	int32 windowLeft = windowRect.left;
	int32 windowTop = windowRect.top;
	if (createInfo.MoveRectCenter)
	{
		windowLeft = (::GetSystemMetrics(SM_CXSCREEN) - rectInfo.GetWidth()) / 2;
		windowTop = (::GetSystemMetrics(SM_CYSCREEN) - rectInfo.GetHeight()) / 2;
	}

	Vector<TCHAR> title = CreateWideStringFromUTF8(createInfo.Title);
	m_handle = ::CreateWindowEx(NULL, WindowsWindow::WindowClassName, title.data(), windowStyle,
		windowLeft, windowTop, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
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

Rect WindowsWindow::GetRect() const
{
	::RECT rect;
	::GetWindowRect(m_handle, &rect);
	return Rect(rect.left, rect.top, rect.right, rect.bottom);
}

}