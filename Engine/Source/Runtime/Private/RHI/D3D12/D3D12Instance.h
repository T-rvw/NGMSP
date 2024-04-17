#pragma once

#include "D3D12Adapter.h"

#include <RHI/IRHIInstance.h>

namespace ow
{

enum class RHIBackend;
struct RHIInstanceCreateInfo;

class D3D12Instance : public IRHIInstance
{
public:
	D3D12Instance() = default;
	D3D12Instance(const RHIInstanceCreateInfo& createInfo);
	D3D12Instance(const D3D12Instance&) = delete;
	D3D12Instance& operator=(const D3D12Instance&) = delete;
	D3D12Instance(D3D12Instance&&) = default;
	D3D12Instance& operator=(D3D12Instance&&) = default;
	virtual ~D3D12Instance();

	virtual RHIBackend GetBackend() const override;
	virtual void EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters) override;

private:
	void InitAdapters();

private:
	ComPtr<IDXGIFactory4> m_factory;
	std::vector<D3D12Adapter> m_adapters;
};

}