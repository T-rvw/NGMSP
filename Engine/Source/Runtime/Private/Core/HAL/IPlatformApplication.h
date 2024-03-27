#pragma once

namespace ow
{

class IPlatformApplication
{
public:
	virtual void Init(void* pInstance, void* pIcon) = 0;
	virtual void* GetProcessInstance() const = 0;
	virtual void Tick() = 0;
};

}