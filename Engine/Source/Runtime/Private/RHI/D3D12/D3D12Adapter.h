#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIAdapter.h>

namespace ow
{

class IRHIDevice;

class D3D12Adapter : public IRHIAdapter
{
public:
	D3D12Adapter() = default;
	explicit D3D12Adapter(IDXGIAdapter1* pAdapter);
	D3D12Adapter(const D3D12Adapter&) = delete;
	D3D12Adapter& operator=(const D3D12Adapter&) = delete;
	D3D12Adapter(D3D12Adapter&&) = default;
	D3D12Adapter& operator=(D3D12Adapter&&) = default;
	virtual ~D3D12Adapter() = default;

	virtual void Initialize() override;
	virtual void EnumerateCommandQueues(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs) override;

private:
	void SetType(const DXGI_ADAPTER_DESC1& desc);
	ComPtr<ID3D12Device> CreateDevice(const RHIDeviceCreateInfo& deviceCI);

private:
	friend class D3D12RHIModule;
	ComPtr<IDXGIAdapter1> m_adapter;
	std::vector<RHICommandQueueCreateInfo> m_commandQueueCIs;
};

}