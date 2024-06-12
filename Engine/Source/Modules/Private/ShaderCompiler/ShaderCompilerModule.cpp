#include "ShaderCompilerModule.h"

#include <Core/Misc/FileLoader.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxc/dxcapi.h>
#include <dxc/d3d12shader.h>
#include <windows.h>

#define D3D12_VERIFY(result) Assert((HRESULT)result >= 0)

namespace ow
{

C_ABI RHI_API IModule* InitializeModule()
{
	return new ShaderCompilerModule();
}

ShaderCompilerModule::ShaderCompilerModule()
{
	LoadDXC();
}

void ShaderCompilerModule::LoadDXC()
{
	m_dxcModule.SetModuleName("[ShaderCompiler][DXC]");
	m_dxcModule.SetModulePath("dxcompiler");
	Assert(m_dxcModule.Load());

	using DxcCreateInstanceFunc = decltype(&DxcCreateInstance);
	auto DxcCreateInstance = (DxcCreateInstanceFunc)m_dxcModule.GetFunctionAddress("DxcCreateInstance");
	D3D12_VERIFY(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(m_pDxcCompiler.GetAddressOf())));
	D3D12_VERIFY(DxcCreateInstance(CLSID_DxcValidator, IID_PPV_ARGS(m_pDxcValidator.GetAddressOf())));
	D3D12_VERIFY(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(m_pDxcUtils.GetAddressOf())));
	D3D12_VERIFY(m_pDxcUtils->CreateDefaultIncludeHandler(m_pDxcIncludeHandler.GetAddressOf()));
}

void ShaderCompilerModule::CompileShader(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo)
{
	return CompileShader(FileLoader::LoadBinary(pShaderFilePath), compileInfo);
}

void ShaderCompilerModule::CompileShader(Vector<std::byte> fileBlob, const ShaderCompileInfo& compileInfo)
{

}

}
