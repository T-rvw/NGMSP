#pragma once

#include "D3D12Header.h"

#include <RHI/RHITypes.h>

namespace ow
{

extern D3D12_BLEND ToD3D12(const RHIBlendType& rhiType);
extern D3D12_BLEND_OP ToD3D12(const RHIBlendOperation& rhiType);
extern D3D12_COMMAND_LIST_TYPE ToD3D12(const RHICommandType& rhiType);
extern D3D12_CULL_MODE ToD3D12(const RHICullMode& rhiType);
extern DXGI_FORMAT ToD3D12(const RHIFormat& rhiType);

}