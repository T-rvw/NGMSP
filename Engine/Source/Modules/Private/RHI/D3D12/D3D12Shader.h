#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIShader.h>

namespace ow
{

class D3D12Shader : public IRHIShader
{
public:
	D3D12Shader() = default;
	D3D12Shader(const D3D12Shader&) = delete;
	D3D12Shader& operator=(const D3D12Shader&) = delete;
	D3D12Shader(D3D12Shader&&) = default;
	D3D12Shader& operator=(D3D12Shader&&) = default;
	virtual ~D3D12Shader() = default;

	RefCountPtr<ID3DBlob> GetHandle() const { return m_shaderBlob; }

private:
	RefCountPtr<ID3DBlob> m_shaderBlob;
};

}