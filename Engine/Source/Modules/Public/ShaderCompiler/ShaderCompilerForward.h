#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IShaderCompilerModule;

using ShaderCompilerModuleHandle = RefCountPtr<IShaderCompilerModule>;

}