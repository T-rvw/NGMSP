#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class IPlatformApplication;

/// <summary>
/// Application means the launching program which contains one or more windows.
/// Or it is headless without GUI windows, such as a batch to process data.
/// </summary>
class ENGINE_API PlatformApplication
{
public:
	PlatformApplication();
	PlatformApplication(const PlatformApplication&) = delete;
	PlatformApplication& operator=(const PlatformApplication&) = delete;
	PlatformApplication(PlatformApplication&& other) noexcept;
	PlatformApplication& operator=(PlatformApplication&& other) noexcept;
	~PlatformApplication();

	void Init(void* pInstance, void* pIcon = nullptr);
	void* GetProcessInstance() const;
	void Run();

private:
	IPlatformApplication* m_pImpl = nullptr;
};

}