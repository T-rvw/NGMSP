#include "D3D12Instance.h"

#include "D3D12Adapter.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Instance::~D3D12Instance()
{
}

RHIBackend D3D12Instance::GetBackend() const
{
	return RHIBackend::D3D12;
}

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

	InitAdapters();
}

void D3D12Instance::InitAdapters()
{
	ComPtr<IDXGIAdapter1> adapter;
	for (uint32 adapterIndex = 0; D3D12_SUCCEED(m_factory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
	{
		m_adapters.emplace_back(adapter.Get());
	}
}

void D3D12Instance::EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters)
{
	if (!pAdapters)
	{
		adapterCount = static_cast<uint32>(m_adapters.size());
		return;
	}

	for (uint32 adapterIndex = 0; adapterIndex < adapterCount; ++adapterIndex)
	{
		pAdapters[adapterIndex] = &m_adapters[adapterIndex];
	}
}

}