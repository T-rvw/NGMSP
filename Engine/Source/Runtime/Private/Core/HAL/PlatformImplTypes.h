#pragma once

#ifdef PLATFORM_WINDOWS
#include "Windows/WindowsApplication.h"
#include "Windows/WindowsEvent.h"
#include "Windows/WindowsModule.h"
#include "Windows/WindowsProcess.h"
#include "Windows/WindowsWindow.h"
#include "Windows/WindowsSemaphore.h"
#include "Windows/WindowsTime.h"
#endif

namespace ow
{

#ifdef PLATFORM_WINDOWS
using PlatformApplicationImpl = WindowsApplication;
using PlatformEventImpl = WindowsEvent;
using PlatformModuleImpl = WindowsModule;
using PlatformProcessImpl = WindowsProcess;
using PlatformSemaphoreImpl = WindowsSemaphore;
using PlatformWindowImpl = WindowsWindow;
#endif

}