#include "D3D12RHIModule.h"

#include "D3D12Instance.h"

#include <RHI/RHITypes.h>

namespace ow
{

C_ABI RHI_API IModule* InitializeModule()
{
	return new D3D12RHIModule();
}

RefCountPtr<IRHIInstance> D3D12RHIModule::CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Instance>(createInfo);
}

}