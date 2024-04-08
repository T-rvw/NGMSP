#pragma once

#include <Core/HAL/APIDefinition.h>
#include <Core/HAL/BasicTypes.h>

namespace ow
{

class IPlatformSemaphore;

/// <summary>
/// Semaphore is a counter used to synchronization orders of multiple threads/processes. 
/// </summary>
class ENGINE_API PlatformSemaphore
{
public:
	PlatformSemaphore();
	PlatformSemaphore(const PlatformSemaphore&) = delete;
	PlatformSemaphore& operator=(const PlatformSemaphore&) = delete;
	PlatformSemaphore(PlatformSemaphore&& other) noexcept;
	PlatformSemaphore& operator=(PlatformSemaphore&& other) noexcept;
	~PlatformSemaphore();

	void Init(int32 initialCount = 0, int32 maxCount = 1);
	void Wait() const;
	void Signal(int32 releaseCount) const;

private:
	IPlatformSemaphore* m_pImpl = nullptr;
};

}