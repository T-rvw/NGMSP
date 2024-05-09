#pragma once

#include <Core/Base/Vector.h>

namespace ow
{

struct WindowCreateInfo;

class IPlatformWindow
{
public:
	virtual ~IPlatformWindow() {}

	virtual void Init(const WindowCreateInfo& createInfo, void* pInstance) = 0;
	virtual void* GetHandle() const = 0;
	virtual Vector<char> GetTitle() const = 0;
	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;
};

}