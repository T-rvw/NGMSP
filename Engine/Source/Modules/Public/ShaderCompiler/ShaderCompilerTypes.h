#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/Containers/Vector.h>
#include <Core/String/String.h>
#include <RHI/IRHIShader.h>
#include <RHI/RHIEnums.h>

namespace ow
{

enum class ShaderCompileFeatures
{
	DebugInfo,
	NoOptimization
};
using ShaderCompileFeatureFlags = BitFlags<ShaderCompileFeatures>;

struct ShaderCompileInfo
{
	RHIShaderLanguage Source;
	RHIShaderLanguage Target;
	RHIShaderType Type;
	ShaderCompileFeatureFlags Features;
	String FileName;
	String EntryPointName;
	Vector<String> Defines;
	Vector<String> IncludeDirectories;
};

struct ShaderCompileResult
{
	String ErrorMessage;
	String ValidateMessgae;
	uint64 ShaderHash[2];
	RefCountPtr<IRHIShader> ShaderBlob;
};

}