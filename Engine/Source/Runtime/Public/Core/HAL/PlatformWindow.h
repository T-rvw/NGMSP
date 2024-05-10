#pragma once

#include <Core/Container/Vector.h>
#include <Core/HAL/APIDefines.h>
#include <Core/HAL/BasicTypes.h>
#include <Core/Math/Rect.hpp>

namespace ow
{

class IPlatformWindow;
struct WindowCreateInfo;

/// <summary>
/// Window means a GUI proxy which combines user inputs and graphics backend or other modules.
/// Output rendering image to window client or do something based on user inputs.
/// </summary>
class CORE_API PlatformWindow final
{
public:
	PlatformWindow();
	PlatformWindow(const PlatformWindow&) = delete;
	PlatformWindow& operator=(const PlatformWindow&) = delete;
	PlatformWindow(PlatformWindow&& other);
	PlatformWindow& operator=(PlatformWindow&& other);
	~PlatformWindow();

	void Init(const WindowCreateInfo& createInfo, void* pInstance = nullptr);
	bool IsValid() const;
	void* GetHandle() const;
	Vector<char> GetTitle() const;
	Rect GetRect() const;

private:
	IPlatformWindow* m_pImpl = nullptr;
};

}