#pragma once

#include <Core/HAL/PlatformModule.h>

#include "D3D12Loader.h"

namespace ow
{

D3D12CreateDeviceFunc D3D12CreateDevice;
D3D12GetDebugInterfaceFunc D3D12GetDebugInterface;

PlatformModule LoadD3D12Modules()
{
	PlatformModule d3d12Dll;
	d3d12Dll.Init("d3d12.dll");

	LOAD_MODULE_API(d3d12Dll, D3D12CreateDevice);
	LOAD_MODULE_API(d3d12Dll, D3D12GetDebugInterface);

	return d3d12Dll;
}

}