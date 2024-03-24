#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class PlatformApplicationImpl;

class ENGINE_API PlatformApplication
{
public:
	PlatformApplication();
	PlatformApplication(const PlatformApplication&) = delete;
	PlatformApplication& operator=(const PlatformApplication&) = delete;
	PlatformApplication(PlatformApplication&& other) noexcept;
	PlatformApplication& operator=(PlatformApplication&& other) noexcept;
	~PlatformApplication();

private:
	PlatformApplicationImpl* m_pImpl = nullptr;
};

}