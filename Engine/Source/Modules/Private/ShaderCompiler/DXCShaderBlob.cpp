#include "DXCShaderBlob.h"

#include <RHI/RHITypes.h>

namespace ow
{

DXCShaderBlob::DXCShaderBlob(void* pData, uint32 dataSize)
{
	auto* pDataBegin = static_cast<uint8*>(pData);
	m_shaderBlob.assign(pDataBegin, pDataBegin + dataSize);
}

}