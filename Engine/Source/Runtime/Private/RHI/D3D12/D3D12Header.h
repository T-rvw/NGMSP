#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3D12MemoryAllocator/D3D12MemAlloc.h>

#include "D3D12Types.h"

#include <Core/Base/TypeTraits.h>

#include <wrl.h>

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

#include <cassert>

#define D3D12_SUCCEED(result) (HRESULT)result >= 0
#define D3D12_VERIFY(result) assert((HRESULT)result >= 0)