#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIInstance.h>

namespace ow
{

struct RHIInstanceCreateInfo;

class D3D12Instance : public IRHIInstance
{
public:
	D3D12Instance() = default;
	D3D12Instance(const D3D12Instance&) = delete;
	D3D12Instance& operator=(const D3D12Instance&) = delete;
	D3D12Instance(D3D12Instance&&) = default;
	D3D12Instance& operator=(D3D12Instance&&) = default;
	virtual ~D3D12Instance() = default;

	virtual void Init(const RHIInstanceCreateInfo& createInfo) override;
	virtual void* GetHandle() const override { return nullptr; }
	virtual std::vector<std::unique_ptr<RHIAdapter>> EnumAdapters() override;

private:
	CComPtr<IDXGIFactory4> m_factory;
};

}