#pragma once

namespace ow
{

struct WindowCreateInfo;

class IPlatformWindow
{
public:
	virtual void Init(const WindowCreateInfo& createInfo, void* pInstance) = 0;
	virtual void* GetHandle() const = 0;
};

}