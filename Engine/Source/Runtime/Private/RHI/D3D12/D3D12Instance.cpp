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

RHIBackend D3D12Instance::GetBackend() const
{
	return RHIBackend::D3D12;
}

std::vector<std::unique_ptr<RHIAdapter>> D3D12Instance::EnumAdapters() const
{
	std::vector<std::unique_ptr<RHIAdapter>> rhiAdapters;

	auto CreateRHIAdapter = [&rhiAdapters](IDXGIAdapter1* pAdapter, bool skipSoftwareAdapter = false)
	{
		DXGI_ADAPTER_DESC1 adapterDesc;
		pAdapter->GetDesc1(&adapterDesc);

		if (skipSoftwareAdapter && (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
		{
			return;
		}

		char adapterName[256];
		sprintf_s(adapterName, "%ws", adapterDesc.Description);

		auto d3d12Adapter = std::make_unique<D3D12Adapter>(pAdapter);
		d3d12Adapter->SetName(adapterName);
		d3d12Adapter->SetType(adapterDesc);
		d3d12Adapter->SetVendor(adapterDesc.VendorId);
		d3d12Adapter->SetVideoMemorySize(adapterDesc.DedicatedVideoMemory);
		d3d12Adapter->SetSystemMemorySize(adapterDesc.DedicatedSystemMemory);
		d3d12Adapter->SetSharedMemorySize(adapterDesc.SharedSystemMemory);

		auto& pRHIAdapter = rhiAdapters.emplace_back(std::make_unique<RHIAdapter>());
		pRHIAdapter->Reset(MoveTemp(d3d12Adapter));
	};

	IDXGIAdapter1* adapter;
	for (uint32 adapterIndex = 0; D3D12_SUCCEED(m_factory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
	{
		CreateRHIAdapter(adapter);
	}

	m_factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter));
	CreateRHIAdapter(adapter);

	return rhiAdapters;
}

}