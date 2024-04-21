#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIAdapter.h>

#include <vector>

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

	virtual void Initialize() override;
	virtual void EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos) override;
	virtual void EnumerateCommandQueues(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs) override;

	RefCountPtr<IDXGIFactory6> GetFactory() const;

private:
	friend class D3D12RHIModule;
	void SetType(const DXGI_ADAPTER_DESC3& desc);
	RefCountPtr<ID3D12Device> CreateDevice(const RHIDeviceCreateInfo& deviceCI);

private:
	RefCountPtr<IDXGIAdapter4> m_adapter;
	const D3D12Instance* m_pInstance = nullptr;
	std::vector<RHIOutputInfo> m_outputInfos;
	std::vector<RHICommandQueueCreateInfo> m_commandQueueCIs;
};

}