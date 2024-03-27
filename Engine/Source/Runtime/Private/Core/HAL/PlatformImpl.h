#pragma once

#ifdef PLATFORM_WINDOWS
#include "Windows/WindowsApplication.h"
#include "Windows/WindowsModule.h"
#include "Windows/WindowsWindow.h"
#endif

namespace ow
{

#ifdef PLATFORM_WINDOWS
using PlatformApplicationImpl = WindowsApplication;
using PlatformModuleImpl = WindowsModule;
using PlatformWindowImpl = WindowsWindow;
#endif

}