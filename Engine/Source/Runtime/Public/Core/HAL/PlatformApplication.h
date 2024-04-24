#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IApplication;
class IPlatformApplication;

/// <summary>
/// Application is the current launching program which contains one or more windows.
/// Or it is headless without GUI windows, such as a batch process to process data.
/// </summary>
class CORE_API PlatformApplication
{
public:
	PlatformApplication() = delete;
	explicit PlatformApplication(IApplication* pApplication);
	PlatformApplication(const PlatformApplication&) = delete;
	PlatformApplication& operator=(const PlatformApplication&) = delete;
	PlatformApplication(PlatformApplication&& other);
	PlatformApplication& operator=(PlatformApplication&& other);
	~PlatformApplication();

	void Init(IApplication* pApplication);
	void* GetProcessInstance() const;
	void Run();

private:
	IApplication* m_pApplication = nullptr;
	IPlatformApplication* m_pImpl = nullptr;
};

}