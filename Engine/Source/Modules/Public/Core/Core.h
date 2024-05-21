#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/Base/NameOf.h>
#include <Core/Base/Optional.h>
#include <Core/Base/RefCountPtr.h>
#include <Core/Base/TypeTraits.h>
#include <Core/Containers/HashMap.h>
#include <Core/Containers/Map.h>
#include <Core/Containers/Vector.h>
#include <Core/Delegates/Delegate.hpp>
#include <Core/Delegates/MulticastDelegate.hpp>
#include <Core/HAL/PlatformApplication.h>
#include <Core/HAL/PlatformEvent.h>
#include <Core/HAL/PlatformModule.h>
#include <Core/HAL/PlatformProcess.h>
#include <Core/HAL/PlatformWindow.h>
#include <Core/HAL/PlatformTime.h>
#include <Core/HAL/PlatformTypes.h>
#include <Core/Hash/FastCRC32.h>
#include <Core/Hash/FNV1A.h>
#include <Core/Math/Box.hpp>
#include <Core/Math/Color.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Quaternion.hpp>
#include <Core/Math/Ray.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Misc/CommandLine.h>
#include <Core/Modules/ModuleManager.h>
#include <Core/String/CString.h>
#include <Core/String/Path.h>
#include <Core/String/String.h>
#include <Core/String/StringID.h>
#include <Core/String/StringView.h>