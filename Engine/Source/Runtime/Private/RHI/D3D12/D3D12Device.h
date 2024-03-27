#pragma once

namespace ow
{

struct RHIDeviceCreateInfo;

class D3D12Device
{
public:
	D3D12Device() = default;
	D3D12Device(const D3D12Device&) = delete;
	D3D12Device& operator=(const D3D12Device&) = delete;
	D3D12Device(D3D12Device&&) = default;
	D3D12Device& operator=(D3D12Device&&) = default;
	~D3D12Device() = default;

	void Init(const RHIDeviceCreateInfo& createInfo);
};

}