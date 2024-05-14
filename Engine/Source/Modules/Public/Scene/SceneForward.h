#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class ISceneModule;

using SceneModuleHandle = RefCountPtr<ISceneModule>;

}