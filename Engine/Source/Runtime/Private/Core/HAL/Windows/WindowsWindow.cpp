#include <Core/HAL/PlatformTypes.h>

#include "WindowsWindow.h"

namespace ow
{

const TCHAR WindowsWindow::WindowClassName[] = TEXT("OW_WindowClass");

void WindowsWindow::Init(const WindowCreateInfo& createInfo, void* pInstance)
{
	int32 windowWidth = createInfo.Width;
	int32 windowHeight = createInfo.Height;
	uint32 windowStyle = WS_OVERLAPPEDWINDOW;

	RECT windowRect = { 0, 0, windowWidth, windowHeight };
	::AdjustWindowRect(&windowRect, windowStyle, FALSE);

	std::vector<TCHAR> title = CreateWideStringFromUTF8(createInfo.Title);
	m_handle = ::CreateWindowEx(NULL, WindowsWindow::WindowClassName, title.data(), windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		(HWND)createInfo.ParentWindow, NULL, (HINSTANCE)pInstance, NULL);
	assert(m_handle);
	ShowWindow(m_handle, SW_SHOW);
}

void* WindowsWindow::GetHandle() const
{
	return m_handle;
}

}