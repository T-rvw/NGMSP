#pragma once

#include <d3d12.h>

namespace ow
{

using D3D12CreateDeviceFunc = HRESULT(WINAPI*)(
    _In_opt_ IUnknown* pAdapter,
    D3D_FEATURE_LEVEL       MinimumFeatureLevel,
    _In_ REFIID             riid,
    _COM_Outptr_opt_ void** ppDevice);

using D3D12GetDebugInterfaceFunc = HRESULT(WINAPI*)(
    _In_ REFIID             riid,
    _COM_Outptr_opt_ void** ppvDebug);

extern D3D12CreateDeviceFunc           D3D12CreateDevice;
extern D3D12GetDebugInterfaceFunc      D3D12GetDebugInterface;

static PlatformModule LoadD3D12Modules()
{
	PlatformModule d3d12Dll;
	d3d12Dll.Init("d3d12.dll");

	LOAD_MODULE_API(d3d12Dll, D3D12CreateDevice);
	LOAD_MODULE_API(d3d12Dll, D3D12GetDebugInterface);

	return d3d12Dll;
}

}