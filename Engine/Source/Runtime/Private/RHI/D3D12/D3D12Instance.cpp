#include "D3D12Instance.h"

#include "D3D12Adapter.h"

#include <RHI/RHITypes.h>

namespace ow
{

void D3D12Instance::Init(const RHIInstanceCreateInfo& createInfo)
{
	// GPU validator needs to enable debug layer at first.
	if (createInfo.Validation != RHIValidationMode::Disabled)
	{
		ID3D12Debug1* pDebugController;
		D3D12_VERIFY(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController)));
		assert(pDebugController);
		pDebugController->EnableDebugLayer();
		pDebugController->SetEnableGPUBasedValidation(RHIValidationMode::GPU == createInfo.Validation);
		pDebugController->Release();
	}

	D3D12_VERIFY(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_factory)));
	assert(m_factory);
}

RHIBackend D3D12Instance::GetBackend() const
{
	return RHIBackend::D3D12;
}

std::vector<IRHIAdapter*> D3D12Instance::EnumerateAdapters() const
{
	std::vector<IRHIAdapter*> rhiAdapters;

	IDXGIAdapter1* pAdapter;
	for (uint32 adapterIndex = 0; D3D12_SUCCEED(m_factory->EnumAdapters1(adapterIndex, &pAdapter)); ++adapterIndex)
	{
		auto& rhiAdapter = rhiAdapters.emplace_back();
	}

	return rhiAdapters;
}

}