#pragma once

#include "D3D12Header.h"

#include <Core/Containers/Vector.h>
#include <RHI/IRHIAdapter.h>

namespace ow
{

struct RHIDeviceCreateInfo;

class D3D12Instance;

class D3D12Adapter : public IRHIAdapter
{
public:
	D3D12Adapter() = delete;
	explicit D3D12Adapter(const D3D12Instance* pInstance, RefCountPtr<IDXGIAdapter4> pAdapter);
	D3D12Adapter(const D3D12Adapter&) = delete;
	D3D12Adapter& operator=(const D3D12Adapter&) = delete;
	D3D12Adapter(D3D12Adapter&&) = default;
	D3D12Adapter& operator=(D3D12Adapter&&) = default;
	virtual ~D3D12Adapter() = default;

	virtual void EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos) override;
	virtual DeviceHandle CreateDevice(const RHIDeviceCreateInfo& createInfo) override;

	RefCountPtr<IDXGIAdapter4> GetHandle() const { return m_adapter; }
	RefCountPtr<IDXGIFactory6> GetFactory() const;

private:
	void SetType(const DXGI_ADAPTER_DESC3& desc);

private:
	const D3D12Instance* m_pInstance;
	Vector<RHIOutputInfo> m_outputInfos;

	RefCountPtr<IDXGIAdapter4> m_adapter;
};

}