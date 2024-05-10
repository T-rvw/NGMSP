#pragma once

#include <Core/HAL/APIDefines.h>

namespace ow
{

class IPlatformProcess;

/// <summary>
/// Process is program's runtime context applied by operating system.
/// </summary>
class CORE_API PlatformProcess final
{
public:
	PlatformProcess();
	PlatformProcess(const PlatformProcess&) = delete;
	PlatformProcess& operator=(const PlatformProcess&) = delete;
	PlatformProcess(PlatformProcess&& other);
	PlatformProcess& operator=(PlatformProcess&& other);
	~PlatformProcess();

	bool Init();

private:
	IPlatformProcess* m_pImpl = nullptr;
};

}