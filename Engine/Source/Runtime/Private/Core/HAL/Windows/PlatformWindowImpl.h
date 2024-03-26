#pragma once

#include <Core/HAL/Platform/Windows/WindowsPlatform.hpp>

namespace ow
{

struct WindowCreateInfo;

class PlatformWindowImpl
{
public:
	static const TCHAR WindowClassName[];

public:
	PlatformWindowImpl() = default;
	PlatformWindowImpl(const PlatformWindowImpl&) = delete;
	PlatformWindowImpl& operator=(const PlatformWindowImpl&) = delete;
	PlatformWindowImpl(PlatformWindowImpl&&) = default;
	PlatformWindowImpl& operator=(PlatformWindowImpl&&) = default;
	~PlatformWindowImpl() = default;

	void Init(const WindowCreateInfo& createInfo, void* pInstance);
	HWND GetHandle() const;

private:
	HWND m_handle;
};

}