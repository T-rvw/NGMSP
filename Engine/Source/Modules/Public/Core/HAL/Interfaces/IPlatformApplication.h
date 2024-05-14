#pragma once

namespace ow
{

class IPlatformApplication
{
public:
	virtual ~IPlatformApplication() {}
	virtual bool PollMessages() = 0;
	virtual void* GetProcessInstance() const = 0;
};

}