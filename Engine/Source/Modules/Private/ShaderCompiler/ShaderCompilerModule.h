#pragma once

#include <ShaderCompiler/IShaderCompilerModule.h>

#include <Core/HAL/PlatformModule.h>

struct IDxcCompiler3;
struct IDxcValidator;
struct IDxcUtils;
struct IDxcIncludeHandler;

namespace ow
{

class ShaderCompilerModule : public IShaderCompilerModule
{
public:
	ShaderCompilerModule();

	virtual void CompileShader(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo) override;
	virtual void CompileShader(Vector<std::byte> fileBlob, const ShaderCompileInfo& compileInfo) override;

private:
	void LoadDXC();

private:
	PlatformModule m_dxcModule;
	RefCountPtr<IDxcCompiler3> m_pDxcCompiler;
	RefCountPtr<IDxcValidator> m_pDxcValidator;
	RefCountPtr<IDxcUtils> m_pDxcUtils;
	RefCountPtr<IDxcIncludeHandler> m_pDxcIncludeHandler;
	
};

}