#include "D3D12Adapter.h"

#include "D3D12Device.h"

#include <RHI/RHIDevice.h>

namespace ow
{

D3D12Adapter::D3D12Adapter(IDXGIAdapter1* pAdapter) :
	m_adapter(pAdapter)
{
}

void D3D12Adapter::Init()
{
}

void D3D12Adapter::SetType(const DXGI_ADAPTER_DESC1& desc)
{
	auto& info = GetInfo();

	if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
	{
		info.Type = GPUAdapterType::CPU;
	}
	else
	{
		// TODO : Check integrated adapter in a correct way.
		// bool isIntegratedAdapter = 0 == desc.DedicatedVideoMemory;
		bool isIntegratedAdapter = GPUVendor::Intel == GetGPUVendor(desc.VendorId);
		info.Type = isIntegratedAdapter ? GPUAdapterType::Integrated : GPUAdapterType::Discrete;
	}
}

std::vector<RHICommandQueueCreateInfo> D3D12Adapter::QueryCommandQueueCreateInfos()
{
	std::vector<RHICommandQueueCreateInfo> createInfos;

	{
		auto& commandQueue = createInfos.emplace_back();
		commandQueue.Type = RHICommandQueueType::Graphics;
		commandQueue.Priority = static_cast<float>(D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
	}

	{
		auto& commandQueue = createInfos.emplace_back();
		commandQueue.Type = RHICommandQueueType::Compute;
		commandQueue.Priority = static_cast<float>(D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
	}

	{
		auto& commandQueue = createInfos.emplace_back();
		commandQueue.Type = RHICommandQueueType::Copy;
		commandQueue.Priority = static_cast<float>(D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
	}

	{
		auto& commandQueue = createInfos.emplace_back();
		commandQueue.Type = RHICommandQueueType::VideoDecode;
		commandQueue.Priority = static_cast<float>(D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
	}

	return createInfos;
}

RHIDevice D3D12Adapter::CreateDevice(const RHIDeviceCreateInfo& deviceCI, const std::vector<RHICommandQueueCreateInfo>& commandQueueCIs) const
{
	ID3D12Device* pDevice;
	D3D12_VERIFY(D3D12CreateDevice(m_adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&pDevice)));
	assert(pDevice);

	auto d3d12Device = std::make_unique<D3D12Device>(pDevice);

	RHIDevice device;
	device.Reset(MoveTemp(d3d12Device));
	return device;
}

}