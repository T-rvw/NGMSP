#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIInstance.h>

namespace ow
{

enum class RHIBackend;
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

	virtual RHIBackend GetBackend() const override;
	virtual void* GetHandle() const override { return m_factory.Get(); }

	virtual std::vector<IRHIAdapter*> EnumerateAdapters() const override;

private:
	ComPtr<IDXGIFactory4> m_factory;
};

}