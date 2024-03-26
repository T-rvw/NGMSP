#include <Core/HAL/PlatformModule.h>

#include "D3D12Loader.h"

namespace ow::gpu
{

PlatformModule LoadD3D12Modules()
{
	PlatformModule d3d12Dll;
	d3d12Dll.Init("d3d12.dll");

	LOAD_MODULE_API(d3d12Dll, D3D12CreateDevice);
	LOAD_MODULE_API(d3d12Dll, D3D12GetDebugInterface);

	return d3d12Dll;
}

}