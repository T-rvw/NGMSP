#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIAdapter.h>

namespace ow
{

class RHIDevice;

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

	virtual void Init() override;
	virtual void* GetHandle() const override { return m_adapter.Get(); }

	void SetType(const DXGI_ADAPTER_DESC1& desc);

	std::unique_ptr<RHIDevice> CreateDevice(const RHIDeviceCreateInfo& createInfo) const;

private:
	ComPtr<IDXGIAdapter1> m_adapter;
};

}