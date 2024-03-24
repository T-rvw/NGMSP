#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class PlatformWindowImpl;
struct WindowCreateInfo;

class ENGINE_API PlatformWindow
{
public:
	PlatformWindow();
	explicit PlatformWindow(const WindowCreateInfo& createInfo, void* pParentWindow = nullptr);
	PlatformWindow(const PlatformWindow&) = delete;
	PlatformWindow& operator=(const PlatformWindow&) = delete;
	PlatformWindow(PlatformWindow&& other) noexcept;
	PlatformWindow& operator=(PlatformWindow&& other) noexcept;
	~PlatformWindow();

	bool IsValid() const;
	void* GetHandle() const;

private:
	PlatformWindowImpl* m_pImpl = nullptr;
};

}