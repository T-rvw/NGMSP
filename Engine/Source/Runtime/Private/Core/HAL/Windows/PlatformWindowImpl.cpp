#include <Core/HAL/WindowCreateInfo.h>

#include "PlatformWindowImpl.h"

namespace ow
{

PlatformWindowImpl::PlatformWindowImpl(const WindowCreateInfo& createInfo, void* pParentWindow)
{
	Init(createInfo, pParentWindow);
}

void PlatformWindowImpl::Init(const WindowCreateInfo& createInfo, void* pParentWindow)
{
	int32 windowX = createInfo.PositionX;
	int32 windowY = createInfo.PositionY;
	int32 windowWidth = createInfo.Width;
	int32 windowHeight = createInfo.Height;
	uint32 windowStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
	uint32 windowExStyle = WS_EX_APPWINDOW;

	if (!createInfo.NoMaximize)
	{
		windowStyle |= WS_MAXIMIZEBOX;
	}

	if (!createInfo.NoMinimize)
	{
		windowStyle |= WS_MINIMIZEBOX;
	}

	if (!createInfo.Borderless)
	{
		windowStyle |= WS_THICKFRAME;
	}
	else
	{
		windowStyle |= WS_BORDER;
	}

	RECT borderRect = { 0, 0, 0, 0 };
	::AdjustWindowRectEx(&borderRect, windowStyle, false, windowExStyle);

	windowX += borderRect.left;
	windowY += borderRect.top;
	windowWidth += borderRect.right - borderRect.left;
	windowHeight += borderRect.bottom - borderRect.top;

	HWND parentWindow = pParentWindow ? (HWND)pParentWindow : NULL;

	WCHAR* pTitle = CreateWideStringFromUTF8(createInfo.Title);
	m_handle = CreateWindowExW(windowExStyle, TEXT("EngineWindowClass"), pTitle, windowStyle,
		windowX, windowY, windowWidth, windowHeight, parentWindow, NULL, NULL, GetModuleHandleW(NULL));
	delete[] pTitle;

	ShowWindow(m_handle, SW_SHOW);
}

HWND PlatformWindowImpl::GetHandle() const
{
	return m_handle;
}

}