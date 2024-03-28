#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIAdapter.h>

namespace ow
{

class D3D12Adapter : public IRHIAdapter
{
public:
	D3D12Adapter() = default;
	D3D12Adapter(const D3D12Adapter&) = delete;
	D3D12Adapter& operator=(const D3D12Adapter&) = delete;
	D3D12Adapter(D3D12Adapter&&) = default;
	D3D12Adapter& operator=(D3D12Adapter&&) = default;
	virtual ~D3D12Adapter() = default;

	virtual void Init() override;
	virtual void* GetHandle() const override { return nullptr; }

	void SetType(uint32 flags);

private:
	IDXGIAdapter1* m_adapter = nullptr;
};

}