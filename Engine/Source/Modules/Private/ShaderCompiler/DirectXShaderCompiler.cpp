#include "DirectXShaderCompiler.h"

#include "DXCShaderBlob.h"

namespace ow
{

DirectXShaderCompiler::DirectXShaderCompiler()
{
	m_dxcModule.SetModuleName("[ShaderCompiler][DXC]");
	m_dxcModule.SetModulePath("dxcompiler");
}

void DirectXShaderCompiler::Init()
{
	Assert(m_dxcModule.Load());

	using DxcCreateInstanceFunc = decltype(&DxcCreateInstance);
	auto DxcCreateInstance = (DxcCreateInstanceFunc)m_dxcModule.GetFunctionAddress("DxcCreateInstance");
	DXC_VERIFY(DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(m_pDxcLibrary.GetAddressOf())));
	DXC_VERIFY(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(m_pDxcCompiler.GetAddressOf())));
	DXC_VERIFY(DxcCreateInstance(CLSID_DxcValidator, IID_PPV_ARGS(m_pDxcValidator.GetAddressOf())));
	DXC_VERIFY(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(m_pDxcUtils.GetAddressOf())));


}

String DirectXShaderCompiler::GetShaderTypeName(RHIShaderType shaderType)
{
	switch (shaderType)
	{
	case RHIShaderType::Compute:
		return "cs";
	case RHIShaderType::Fragment:
		return "ps";
	case RHIShaderType::Mesh:
		return "ms";
	case RHIShaderType::Task:
		return "as";
	case RHIShaderType::Vertex:
		return "vs";
	default:
		return "lib";
	}
}

ShaderCompileResult DirectXShaderCompiler::Compile(const char* pShaderFilePath, const ShaderCompileInfo& compileInfo)
{
	RefCountPtr<IDxcBlobEncoding> dxcBlob;
	DXC_VERIFY(m_pDxcLibrary->CreateBlobFromFile(CreateWideStringFromUTF8(pShaderFilePath).data(), nullptr, &dxcBlob));
	return CompileImpl(dxcBlob, compileInfo);
}

ShaderCompileResult DirectXShaderCompiler::Compile(const Vector<std::byte>& fileBlob, const ShaderCompileInfo& compileInfo)
{
	RefCountPtr<IDxcBlobEncoding> dxcBlob;
	DXC_VERIFY(m_pDxcUtils->CreateBlob(fileBlob.data(), static_cast<uint32>(fileBlob.size()), DXC_CP_ACP, dxcBlob.GetAddressOf()));
	return CompileImpl(dxcBlob, compileInfo);
}

ShaderCompileResult DirectXShaderCompiler::CompileImpl(RefCountPtr<IDxcBlobEncoding> dxcBlob, const ShaderCompileInfo& compileInfo)
{
	DXCArguments compileArguments;

	// Arguments
	compileArguments.AddArgument(compileInfo.FileName.c_str());
	compileArguments.AddArgument("-E", compileInfo.EntryPointName.c_str());
	auto shaderModel = std::format("{}_{}_{}", GetShaderTypeName(compileInfo.Type), m_shaderModelMajorVersion, m_shaderModelMinorVersion);
	compileArguments.AddArgument("-T", shaderModel.c_str());
	compileArguments.AddArgument(L"-HV", L"2021");
	compileArguments.AddArgument(DXC_ARG_ALL_RESOURCES_BOUND);
	compileArguments.AddArgument(DXC_ARG_WARNINGS_ARE_ERRORS);
	compileArguments.AddArgument(DXC_ARG_PACK_MATRIX_ROW_MAJOR);

	if (compileInfo.Features.IsEnabled(ShaderCompileFeatures::DebugInfo))
	{
		// Expect embed pdb data to blob.
		compileArguments.AddArgument(DXC_ARG_DEBUG);
		compileArguments.AddArgument(L"-Qembed_debug");
	}

	if (compileInfo.Features.IsEnabled(ShaderCompileFeatures::NoOptimization))
	{
		compileArguments.AddArgument(DXC_ARG_SKIP_OPTIMIZATIONS);
	}

	if (RHIShaderByteCode::SPIRV == compileInfo.Target)
	{
		compileArguments.AddArgument(L"-spirv");
		compileArguments.AddArgument(L"-fspv-target-env=vulkan1.3");
		compileArguments.AddArgument(L"-fspv-extension=KHR");
		compileArguments.AddArgument(L"-fspv-extension=SPV_NV_mesh_shader");
		compileArguments.AddArgument(L"-fspv-extension=SPV_EXT_descriptor_indexing");
		compileArguments.AddArgument(L"-fspv-extension=SPV_EXT_shader_viewport_index_layer");
		compileArguments.AddArgument(L"-fspv-extension=SPV_GOOGLE_hlsl_functionality1");
		compileArguments.AddArgument(L"-fspv-extension=SPV_GOOGLE_user_type");
		compileArguments.AddArgument(L"-fvk-use-dx-layout");
		compileArguments.AddArgument(L"-fspv-reflect");
	}

	// Includes
	for (const auto& includeDirectory : compileInfo.IncludeDirectories)
	{
		compileArguments.AddArgument("-I", includeDirectory.c_str());
	}

	// Defines
	for (const auto& define : compileInfo.Defines)
	{
		compileArguments.AddDefine(define.c_str());
	}

	auto resultArguments = compileArguments.GetArguments();

	// Compile
	DxcBuffer sourceBuffer;
	sourceBuffer.Ptr = dxcBlob->GetBufferPointer();
	sourceBuffer.Size = dxcBlob->GetBufferSize();
	sourceBuffer.Encoding = DXC_CP_ACP;

	RefCountPtr<IDxcResult> pCompileResult;
	DXC_VERIFY(m_pDxcCompiler->Compile(&sourceBuffer, resultArguments.data(), static_cast<uint32>(resultArguments.size()), nullptr, IID_PPV_ARGS(pCompileResult.GetAddressOf())));

	ShaderCompileResult packedResult;

	// Query error messages.
	RefCountPtr<IDxcBlobUtf8> pCompileErrors;
	if (DXC_SUCCEED(pCompileResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(pCompileErrors.GetAddressOf()), nullptr)))
	{
		if (pCompileErrors && pCompileErrors->GetStringLength())
		{
			packedResult.ErrorMessage = (char*)pCompileErrors->GetStringPointer();
		}
	}

	// Check compile status.
	HRESULT dxcStatus;
	if (FAILED(pCompileResult->GetStatus(&dxcStatus)) || FAILED(dxcStatus))
	{
		printf("[ShaderCompiler] Failed to compile shader %s : %s\n", compileInfo.FileName.c_str(), packedResult.ErrorMessage);
		return packedResult;
	}

	// Get generated shader blob and validate it.
	RefCountPtr<IDxcBlob> shaderBlobData;
	DXC_VERIFY(pCompileResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(shaderBlobData.GetAddressOf()), nullptr));

	auto dxcShaderBlob = MakeRefCountPtr<DXCShaderBlob>(shaderBlobData->GetBufferPointer(), static_cast<uint32>(shaderBlobData->GetBufferSize()));

	//RefCountPtr<IDxcOperationResult> pValidateResult;
	//DXC_VERIFY(m_pDxcValidator->Validate((IDxcBlob*)shaderBlobData.Get(), DxcValidatorFlags_InPlaceEdit, pValidateResult.GetAddressOf()));
	//HRESULT validateStatus;
	//if (FAILED(pValidateResult->GetStatus(&validateStatus)) || FAILED(validateStatus))
	//{
	//	RefCountPtr<IDxcBlobEncoding> pPrintBlob;
	//	DXC_VERIFY(pValidateResult->GetErrorBuffer(pPrintBlob.GetAddressOf()));
	//	RefCountPtr<IDxcBlobUtf8> pPrintBlobUtf8;
	//	DXC_VERIFY(m_pDxcUtils->GetBlobAsUtf8(pPrintBlob.Get(), pPrintBlobUtf8.GetAddressOf()));
	//	compileResult.ValidateMessage = pPrintBlobUtf8->GetStringPointer();
	//	return compileResult;
	//}

	// Get shader hash.
	RefCountPtr<IDxcBlob> pShaderHash;
	if (DXC_SUCCEED(pCompileResult->GetOutput(DXC_OUT_SHADER_HASH, IID_PPV_ARGS(pShaderHash.GetAddressOf()), nullptr)))
	{
		auto* pHashBuf = (DxcShaderHash*)pShaderHash->GetBufferPointer();
		memcpy(packedResult.ShaderHash, pHashBuf->HashDigest, sizeof(uint64) * 2);
	}

	// Get shader reflection.
	//RefCountPtr<IDxcBlob> pReflectionData;
	//if (DXC_SUCCEED(pDxcResult->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(pReflectionData.GetAddressOf()), nullptr)))
	//{
	//	DxcBuffer reflectionBuffer;
	//	reflectionBuffer.Ptr = pReflectionData->GetBufferPointer();
	//	reflectionBuffer.Size = pReflectionData->GetBufferSize();
	//	reflectionBuffer.Encoding = DXC_CP_ACP;
	//
	//	RefCountPtr<IUnknown> pReflection;
	//	DXC_VERIFY(m_pDxcUtils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(pReflection.GetAddressOf())));
	//}
	packedResult.ShaderBlob = dxcShaderBlob;
	packedResult.Status = ShaderCompileStatus::Success;
	return packedResult;
}

}