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
	RHIShaderType Type;
	RHIShaderLanguage Source;
	RHIShaderByteCode Target;
	ShaderCompileFeatureFlags Features;
	String FileName;
	String EntryPointName;
	Vector<String> Defines;
	Vector<String> IncludeDirectories;
};

struct ShaderCompileResult
{
	const char* ErrorMessage;
	const char* ValidateMessage;
	uint64 ShaderHash[2];
	RefCountPtr<IRHIShader> ShaderBlob;
};

}