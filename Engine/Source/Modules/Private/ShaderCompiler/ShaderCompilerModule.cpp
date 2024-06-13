#include "ShaderCompilerModule.h"

#include <Core/Misc/FileLoader.h>

namespace ow
{

C_ABI RHI_API IModule* InitializeModule()
{
	return new ShaderCompilerModule();
}

ShaderCompilerModule::ShaderCompilerModule()
{
	m_dxc.Init();
}

ShaderCompileResult ShaderCompilerModule::CompileShader(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo)
{
	return CompileShader(FileLoader::LoadBinary(pShaderFilePath), compileInfo);
}

ShaderCompileResult ShaderCompilerModule::CompileShader(const Vector<std::byte>& fileBlob, const ShaderCompileInfo& compileInfo)
{
	Assert(RHIShaderLanguage::HLSL == compileInfo.Source);
	return m_dxc.Compile(fileBlob, compileInfo);
}

}
