#pragma once

namespace ow
{

class IPlatformApplication
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

	virtual void* GetProcessInstance() const = 0;
};

}