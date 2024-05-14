#include "D3D12Instance.h"

#include "D3D12Adapter.h"
#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Instance::D3D12Instance(const RHIInstanceCreateInfo& createInfo)
{
	// GPU validator needs to enable debug layer at first.
	if (createInfo.Validation != RHIValidationMode::Disabled)
	{
		RefCountPtr<ID3D12Debug1> pDebugController;
		D3D12_VERIFY(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController)));
		Assert(pDebugController);
		pDebugController->EnableDebugLayer();
		pDebugController->SetEnableGPUBasedValidation(RHIValidationMode::GPU == createInfo.Validation);
		pDebugController->Release();
	}

	D3D12_VERIFY(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_factory)));
	Assert(m_factory);

	InitAdapters();
}

D3D12Instance::~D3D12Instance()
{
}

RHIBackend D3D12Instance::GetBackend() const
{
	return RHIBackend::D3D12;
}

void D3D12Instance::InitAdapters()
{
	uint32 adapterIndex = 0;
	RefCountPtr<IDXGIAdapter4> pAdapter;
	while (D3D12_SUCCEED(m_factory->EnumAdapterByGpuPreference(adapterIndex++, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(pAdapter.ReleaseAndGetAddressOf()))))
	{
		m_adapters.emplace_back(this, pAdapter.Get());
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