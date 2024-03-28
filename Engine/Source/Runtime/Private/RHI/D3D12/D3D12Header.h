#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

#include <atlbase.h>
#include <cassert>

#define D3D12_SUCCEED(result) (HRESULT)result >= 0
#define D3D12_VERIFY(result) assert((HRESULT)result >= 0)