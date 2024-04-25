#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IPlatformApplication;

/// <summary>
/// Application is the current launching program which contains one or more windows.
/// Or it is headless without GUI windows, such as a batch process to process data.
/// </summary>
class CORE_API PlatformApplication
{
public:
	PlatformApplication();
	PlatformApplication(const PlatformApplication&) = delete;
	PlatformApplication& operator=(const PlatformApplication&) = delete;
	PlatformApplication(PlatformApplication&& other);
	PlatformApplication& operator=(PlatformApplication&& other);
	~PlatformApplication();

	bool PollMessages();
	void* GetProcessInstance() const;

private:
	IPlatformApplication* m_pImpl = nullptr;
};

}