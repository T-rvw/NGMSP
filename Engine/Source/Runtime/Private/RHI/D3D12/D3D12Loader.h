#pragma once

#include "D3D12Header.h"

namespace ow
{

class PlatformModule;

using D3D12CreateDeviceFunc = HRESULT(WINAPI*)(
    _In_opt_ IUnknown* pAdapter,
    D3D_FEATURE_LEVEL       MinimumFeatureLevel,
    _In_ REFIID             riid,
    _COM_Outptr_opt_ void** ppDevice);

using D3D12GetDebugInterfaceFunc = HRESULT(WINAPI*)(
    _In_ REFIID             riid,
    _COM_Outptr_opt_ void** ppvDebug);

extern D3D12CreateDeviceFunc D3D12CreateDevice;
extern D3D12GetDebugInterfaceFunc D3D12GetDebugInterface;

extern PlatformModule LoadD3D12Modules();

}