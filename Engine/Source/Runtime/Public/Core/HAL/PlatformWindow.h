#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IPlatformWindow;
struct WindowCreateInfo;

/// <summary>
/// Window means a GUI proxy which combines user inputs and graphics backend or other modules.
/// Output rendering image to window client or do something based on user inputs.
/// </summary>
class ENGINE_API PlatformWindow
{
public:
	PlatformWindow();
	PlatformWindow(const PlatformWindow&) = delete;
	PlatformWindow& operator=(const PlatformWindow&) = delete;
	PlatformWindow(PlatformWindow&& other) noexcept;
	PlatformWindow& operator=(PlatformWindow&& other) noexcept;
	~PlatformWindow();

	void Init(const WindowCreateInfo& createInfo, void* pInstance = nullptr);
	bool IsValid() const;
	void* GetHandle() const;

private:
	IPlatformWindow* m_pImpl = nullptr;
};

}