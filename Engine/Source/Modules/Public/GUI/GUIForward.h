#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IGUIModule;

using GUIModuleHandle = RefCountPtr<IGUIModule>;

}