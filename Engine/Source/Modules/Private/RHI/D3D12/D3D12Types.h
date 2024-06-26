#pragma once

#include "D3D12Header.h"

#include <Core/Math/Box.hpp>
#include <RHI/RHIEnums.h>

namespace ow
{

class D3D12Types final
{
public:
	D3D12Types() = delete;

	static RHIColorSpace ToRHI(DXGI_COLOR_SPACE_TYPE deviceType);

	static D3D12_BLEND ToD3D12(RHIBlendFactor rhiType);
	static D3D12_BLEND_OP ToD3D12(RHIBlendOperation rhiType);
	static DXGI_COLOR_SPACE_TYPE ToD3D12(RHIColorSpace rhiType);
	static D3D12_COMMAND_LIST_TYPE ToD3D12(RHICommandType rhiType);
	static D3D12_CULL_MODE ToD3D12(RHICullMode rhiType);
	static D3D12_FENCE_FLAGS ToD3D12(RHIFenceType rhiType);
	static DXGI_FORMAT ToD3D12(RHIFormat rhiType);
	static D3D12_VIEWPORT ToD3D12(const Viewport& viewport);
	static D3D12_RECT ToD3D12(const Rect& rect);
};

}