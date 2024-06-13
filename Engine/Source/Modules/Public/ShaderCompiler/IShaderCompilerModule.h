#pragma once

#include <Core/Modules/IModule.h>
#include <ShaderCompiler/ShaderCompilerForward.h>
#include <ShaderCompiler/ShaderCompilerTypes.h>

namespace ow
{

class IShaderCompilerModule : public IModule, public RefCountObject
{
public:
	virtual ~IShaderCompilerModule() {}

	virtual ShaderCompileResult CompileShader(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo) = 0;
	virtual ShaderCompileResult CompileShader(const Vector<std::byte>& fileBlob, const ShaderCompileInfo& compileInfo) = 0;
};

}