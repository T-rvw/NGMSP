#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/Base/Hash/FastCRC32.h>
#include <Core/Base/Hash/FNV1A.h>
#include <Core/Base/NameOf.h>
#include <Core/Base/RefCountPtr.h>
#include <Core/Base/StringID.h>
#include <Core/Base/TypeTraits.h>
#include <Core/Modules/IModule.h>
#include <Core/Modules/ModuleManager.h>
#include <Core/HAL/PlatformApplication.h>
#include <Core/HAL/PlatformEvent.h>
#include <Core/HAL/PlatformModule.h>
#include <Core/HAL/PlatformProcess.h>
#include <Core/HAL/PlatformWindow.h>
#include <Core/HAL/PlatformTime.h>
#include <Core/HAL/PlatformTypes.h>