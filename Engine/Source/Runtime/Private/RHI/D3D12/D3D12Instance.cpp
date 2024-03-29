#include "D3D12Instance.h"

#include "D3D12Adapter.h"

#include <RHI/RHIAdapter.h>
#include <RHI/RHITypes.h>

namespace ow
{

void D3D12Instance::Init(const RHIInstanceCreateInfo& createInfo)
{
	// GPU validator needs to enable debug layer at first.
	if (createInfo.EnableDebugLayer || createInfo.EnableGPUValidator)
	{
		ID3D12Debug1* pDebugController;
		D3D12_VERIFY(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController)));
		assert(pDebugController);
		pDebugController->EnableDebugLayer();
		pDebugController->SetEnableGPUBasedValidation(createInfo.EnableGPUValidator);
		pDebugController->Release();
	}

	D3D12_VERIFY(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_factory)));
	assert(m_factory);
}

std::vector<std::unique_ptr<RHIAdapter>> D3D12Instance::EnumAdapters()
{
	std::vector<std::unique_ptr<RHIAdapter>> adapters;

	auto CreateRHIAdapter = [&adapters](IDXGIAdapter1* adapter, bool skipSoftwareAdapter = false)
	{
		DXGI_ADAPTER_DESC1 adapterDesc;
		adapter->GetDesc1(&adapterDesc);

		if (skipSoftwareAdapter && (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
		{
			return;
		}

		char adapterName[256];
		sprintf_s(adapterName, "%ws", adapterDesc.Description);

		auto d3d12Adapter = std::make_unique<D3D12Adapter>();
		d3d12Adapter->SetName(adapterName);
		d3d12Adapter->SetType(adapterDesc.Flags);
		d3d12Adapter->SetVendor(adapterDesc.VendorId);
		d3d12Adapter->SetVRAMSize(adapterDesc.DedicatedVideoMemory);

		auto& pAdapter = adapters.emplace_back(std::make_unique<RHIAdapter>());
		pAdapter->Init(MoveTemp(d3d12Adapter));
	};

	IDXGIAdapter1* adapter;
	for (uint32 adapterIndex = 0; D3D12_SUCCEED(m_factory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
	{
		const bool skipSoftwareAdapter = true;
		CreateRHIAdapter(adapter, skipSoftwareAdapter);
	}

	m_factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter));
	CreateRHIAdapter(adapter);

	return adapters;
}

}