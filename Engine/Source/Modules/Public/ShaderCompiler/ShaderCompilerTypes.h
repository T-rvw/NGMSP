#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/Containers/Vector.h>
#include <Core/Misc/IBlob.h>
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

enum class ShaderCompileStatus
{
	Success,
	SourceNotFound,
	ValidateFailure
};

struct ShaderCompileResult
{
	ShaderCompileStatus Status;
	const char* ErrorMessage;
	const char* ValidateMessage;
	uint64 ShaderHash[2];
	RefCountPtr<IBlob> ShaderBlob;
};

}