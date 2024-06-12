#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/Containers/Vector.h>
#include <Core/Modules/IModule.h>
#include <Core/String/String.h>
#include <RHI/RHIEnums.h>
#include <ShaderCompiler/ShaderCompilerForward.h>

namespace ow
{

enum class ShaderCompileFeatures
{
	DebugMode
};

using ShaderCompileFeatureFlags = BitFlags<ShaderCompileFeatures>;

struct ShaderCompileInfo
{
	RHIShaderLanguage Source;
	RHIShaderLanguage Target;
	ShaderCompileFeatureFlags Features;
	String EntryPointName;
	Vector<String> Arguments;
	Vector<String> Defines;
	Vector<String> IncludeDirectories;
};

class IShaderCompilerModule : public IModule, public RefCountObject
{
public:
	virtual ~IShaderCompilerModule() {}

	virtual void CompileShader(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo) = 0;
	virtual void CompileShader(Vector<std::byte> fileBlob, const ShaderCompileInfo& compileInfo) = 0;
};

}