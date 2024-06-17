#pragma once

#include <Core/Containers/Vector.h>
#include <Core/Misc/IBlob.h>

namespace ow
{

class DXCShaderBlob : public IBlob
{
public:
	DXCShaderBlob() = delete;
	explicit DXCShaderBlob(void* pData, uint32 dataSize);
	DXCShaderBlob(const DXCShaderBlob&) = delete;
	DXCShaderBlob& operator=(const DXCShaderBlob&) = delete;
	DXCShaderBlob(DXCShaderBlob&&) = default;
	DXCShaderBlob& operator=(DXCShaderBlob&&) = default;
	virtual ~DXCShaderBlob() = default;

	const void* GetData() const { return m_shaderBlob.data(); }
	uint32 GetSize() const { return static_cast<uint32>(m_shaderBlob.size()); }

private:
	Vector<uint8> m_shaderBlob;
};

}