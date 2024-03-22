#pragma once

#if defined(PLATFORM_ANDROID)
#include "Android/AndroidPlatform.h"
#elif defined(PLATFORM_IOS)
#include "IOS/IOSPlatform.h"
#elif defined(PLATFORM_LINUX)
#include "Linux/LinuxPlatform.h"
#elif defined(PLATFORM_MAC)
#include "Mac/MacPlatform.h"
#elif defined(PLATFORM_WINDOWS)
#include "Windows/WindowsPlatform.h"
#endif