#pragma once

#include <Core/Base/RefCountPtr.h>
#include <Core/HAL/PlatformModule.h>
#include <Core/HAL/Windows/WindowsUtils.hpp>
#include <ShaderCompiler/ShaderCompilerTypes.h>

#include "DXCHeader.h"

#include <format>

namespace ow
{

class DXCArguments
{
public:
	DXCArguments() = default;
	DXCArguments(const DXCArguments&) = default;
	DXCArguments& operator=(const DXCArguments&) = default;
	DXCArguments(DXCArguments&&) = default;
	DXCArguments& operator=(DXCArguments&&) = default;
	~DXCArguments() = default;

	void AddArgument(const char* pArgument, const char* pValue = nullptr)
	{
		auto argument = CreateWideStringFromUTF8(pArgument);
		auto value = CreateWideStringFromUTF8(pValue);
		AddArgument(argument.data(), value.data());
	}

	void AddArgument(const wchar_t* pArgument, const wchar_t* pValue = nullptr)
	{
		m_arguments.push_back(pArgument);
		if (pValue)
		{
			m_arguments.push_back(pValue);
		}
	}

	void AddDefine(const char* pDefine, const char* pValue = nullptr)
	{
		if (strstr(pDefine, "="))
		{
			AddArgument("-D", pDefine);
		}
		else
		{
			AddArgument("-D", std::format("%s=%s", pDefine, pValue ? pValue : "1").c_str());
		}
	}

	Vector<const wchar_t*> GetArguments()
	{
		Vector<const wchar_t*> arguments;
		arguments.reserve(m_arguments.size());
		for (const auto& arg : m_arguments)
		{
			arguments.push_back(arg.c_str());
		}
		return arguments;
	}

private:
	Vector<WString> m_arguments;
};

class DirectXShaderCompiler
{
public:
	DirectXShaderCompiler();
	DirectXShaderCompiler(const DirectXShaderCompiler&) = delete;
	DirectXShaderCompiler& operator=(const DirectXShaderCompiler&) = delete;
	DirectXShaderCompiler(DirectXShaderCompiler&&) = default;
	DirectXShaderCompiler& operator=(DirectXShaderCompiler&&) = default;
	~DirectXShaderCompiler() = default;

	void Init();
	String GetShaderTypeName(RHIShaderType shaderType);
	ShaderCompileResult Compile(const Vector<std::byte>& fileBlob, const ShaderCompileInfo& compileInfo);

private:
	PlatformModule m_dxcModule;
	RefCountPtr<IDxcCompiler3> m_pDxcCompiler;
	RefCountPtr<IDxcValidator> m_pDxcValidator;
	RefCountPtr<IDxcUtils> m_pDxcUtils;

	// SM 6.6
	uint8 m_shaderModelMajorVersion = 6;
	uint8 m_shaderModelMinorVersion = 6;
};

}