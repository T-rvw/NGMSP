#pragma once

#include "WindowsPlatform.h"

namespace ow
{

struct WindowCreateInfo;

class PlatformWindowImpl
{
public:
	PlatformWindowImpl() = default;
	explicit PlatformWindowImpl(const WindowCreateInfo& createInfo, void* pParentWindow = nullptr);
	PlatformWindowImpl(const PlatformWindowImpl&) = delete;
	PlatformWindowImpl& operator=(const PlatformWindowImpl&) = delete;
	PlatformWindowImpl(PlatformWindowImpl&&) = default;
	PlatformWindowImpl& operator=(PlatformWindowImpl&&) = default;
	~PlatformWindowImpl() = default;

	void Init(const WindowCreateInfo& createInfo, void* pParentWindow = nullptr);
	HWND GetHandle() const;

private:
	HWND m_handle;
};

}