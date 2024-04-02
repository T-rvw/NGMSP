#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIDevice.h>

namespace ow
{

class D3D12Device : public IRHIDevice
{
public:
	D3D12Device() = default;
	explicit D3D12Device(ID3D12Device* pDevice);
	D3D12Device(const D3D12Device&) = delete;
	D3D12Device& operator=(const D3D12Device&) = delete;
	D3D12Device(D3D12Device&&) = default;
	D3D12Device& operator=(D3D12Device&&) = default;
	virtual ~D3D12Device() = default;

	virtual void Init() override;
	virtual void* GetHandle() const override { return m_device.Get(); }

private:
	ComPtr<ID3D12Device> m_device;
};

}