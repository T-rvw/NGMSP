#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IPlatformProcess;

/// <summary>
/// Process is program's runtime context applied by operating system.
/// </summary>
class ENGINE_API PlatformProcess
{
public:
	PlatformProcess();
	PlatformProcess(const PlatformProcess&) = delete;
	PlatformProcess& operator=(const PlatformProcess&) = delete;
	PlatformProcess(PlatformProcess&& other) noexcept;
	PlatformProcess& operator=(PlatformProcess&& other) noexcept;
	~PlatformProcess();

	bool Init();

private:
	IPlatformProcess* m_pImpl = nullptr;
};

}