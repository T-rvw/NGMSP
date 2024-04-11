#include "D3D12RHIModule.h"

#include "D3D12Instance.h"

#include <Core/HAL/APIDefinition.h>

namespace ow
{

C_ABI RHI_API IRHIModule* InitializeModule()
{
	return new D3D12RHIModule();
}

IRHIInstance* D3D12RHIModule::CreateRHIInstance()
{
	return new D3D12Instance();
}

}