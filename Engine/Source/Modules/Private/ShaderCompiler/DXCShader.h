#pragma once

#include "DXCHeader.h"

#include <RHI/IRHIShader.h>

namespace ow
{

class DXCShader : public IRHIShader
{
public:
	DXCShader() = default;
	DXCShader(const DXCShader&) = delete;
	DXCShader& operator=(const DXCShader&) = delete;
	DXCShader(DXCShader&&) = default;
	DXCShader& operator=(DXCShader&&) = default;
	virtual ~DXCShader() = default;

	RefCountPtr<ID3DBlob> GetHandle() const { return m_shaderBlob; }

private:
	RefCountPtr<ID3DBlob> m_shaderBlob;
};

}