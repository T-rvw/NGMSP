#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIAdapter.h>

namespace ow
{

class D3D12Instance;

class D3D12Adapter : public IRHIAdapter
{
public:
	D3D12Adapter() = default;
	explicit D3D12Adapter(const D3D12Instance* pInstance, ComPtr<IDXGIAdapter1> pAdapter);
	D3D12Adapter(const D3D12Adapter&) = delete;
	D3D12Adapter& operator=(const D3D12Adapter&) = delete;
	D3D12Adapter(D3D12Adapter&&) = default;
	D3D12Adapter& operator=(D3D12Adapter&&) = default;
	virtual ~D3D12Adapter() = default;

	virtual void Initialize() override;
	virtual void EnumerateCommandQueues(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs) override;

	ComPtr<IDXGIFactory4> GetFactory() const;

private:
	friend class D3D12RHIModule;
	void SetType(const DXGI_ADAPTER_DESC1& desc);
	ComPtr<ID3D12Device> CreateDevice(const RHIDeviceCreateInfo& deviceCI);

private:
	ComPtr<IDXGIAdapter1> m_adapter;
	const D3D12Instance* m_pInstance = nullptr;
	std::vector<RHICommandQueueCreateInfo> m_commandQueueCIs;
};

}