#pragma once

#include "WindowsPlatform.h"

namespace ow
{

class PlatformApplicationImpl
{
public:
	PlatformApplicationImpl() = default;
	PlatformApplicationImpl(const PlatformApplicationImpl&) = delete;
	PlatformApplicationImpl& operator=(const PlatformApplicationImpl&) = delete;
	PlatformApplicationImpl(PlatformApplicationImpl&&) = default;
	PlatformApplicationImpl& operator=(PlatformApplicationImpl&&) = default;
	~PlatformApplicationImpl() = default;
};

}