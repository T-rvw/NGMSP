#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxc/dxcapi.h>
#include <dxc/d3d12shader.h>

#define DXC_SUCCEED(result) (HRESULT)result >= 0
#define DXC_VERIFY(result) Assert((HRESULT)result >= 0)