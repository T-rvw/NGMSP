#pragma once

#include <ShaderCompiler/IShaderCompilerModule.h>

#include "DirectXShaderCompiler.h"

namespace ow
{

class ShaderCompilerModule : public IShaderCompilerModule
{
public:
	ShaderCompilerModule();
	ShaderCompilerModule(const ShaderCompilerModule&) = delete;
	ShaderCompilerModule& operator=(const ShaderCompilerModule&) = delete;
	ShaderCompilerModule(ShaderCompilerModule&&) = default;
	ShaderCompilerModule& operator=(ShaderCompilerModule&&) = default;
	~ShaderCompilerModule() = default;

	virtual ShaderCompileResult CompileShader(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo) override;
	virtual ShaderCompileResult CompileShader(const Vector<std::byte>& fileBlob, const ShaderCompileInfo& compileInfo) override;

private:
	DirectXShaderCompiler m_dxc;
};

}