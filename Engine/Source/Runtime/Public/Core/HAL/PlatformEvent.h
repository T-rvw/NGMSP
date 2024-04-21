#pragma once

#include <Core/HAL/APIDefinition.h>

namespace ow
{

class IPlatformEvent;

/// <summary>
/// Event is a named or unnamed synchronization object.
/// It allows multiple threads in a single process to communicate with each other.
/// </summary>
class CORE_API PlatformEvent
{
public:
	PlatformEvent();
	PlatformEvent(const PlatformEvent&) = delete;
	PlatformEvent& operator=(const PlatformEvent&) = delete;
	PlatformEvent(PlatformEvent&& other);
	PlatformEvent& operator=(PlatformEvent&& other);
	~PlatformEvent();

	void Init(const char* pName);
	void Shutdown();
	bool IsValid() const;
	void* GetHandle() const;
	void Signal();
	void Wait();

private:
	IPlatformEvent* m_pImpl = nullptr;
};

}