#pragma once

#include <Core/Containers/Vector.h>
#include <Core/Math/Rect.hpp>

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
	virtual Rect GetRect() const = 0;
};

}