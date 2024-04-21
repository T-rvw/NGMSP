#pragma once

namespace ow
{

class IPlatformEvent
{
public:
	virtual ~IPlatformEvent() {}

	virtual void Init(const char* pName) = 0;
	virtual void Shutdown() = 0;

	virtual void* GetHandle() const = 0;
	virtual void Signal() = 0;
	virtual void Wait() = 0;
};

}