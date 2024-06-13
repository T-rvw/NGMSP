#include "ShaderCompilerModule.h"

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
	return m_dxc.Compile(pShaderFilePath, compileInfo);
}

ShaderCompileResult ShaderCompilerModule::CompileShader(const Vector<std::byte>& fileBlob, const ShaderCompileInfo& compileInfo)
{
	return m_dxc.Compile(fileBlob, compileInfo);
}

}
