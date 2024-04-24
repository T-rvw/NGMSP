#pragma once

namespace ow
{

class IPlatformApplication
{
public:
	virtual ~IPlatformApplication() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual bool ShouldQuit() = 0;
	virtual void Shutdown() = 0;

	virtual void* GetProcessInstance() const = 0;
};

}