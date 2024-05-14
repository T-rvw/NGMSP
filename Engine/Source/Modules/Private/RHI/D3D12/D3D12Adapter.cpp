#include "D3D12Adapter.h"

#include "D3D12Instance.h"
#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Adapter::D3D12Adapter(const D3D12Instance* pInstance, RefCountPtr<IDXGIAdapter4> pAdapter) :
	m_pInstance(pInstance),
	m_adapter(MoveTemp(pAdapter))
{
	DXGI_ADAPTER_DESC3 adapterDesc;
	m_adapter->GetDesc3(&adapterDesc);

	char adapterName[256];
	sprintf_s(adapterName, "%ws", adapterDesc.Description);

	SetType(adapterDesc);
	m_info.Name = adapterName;
	m_info.Vendor = GetGPUVendor(adapterDesc.VendorId);
	m_info.DeviceID = adapterDesc.DeviceId;
	m_info.VideoMemorySize = adapterDesc.DedicatedVideoMemory;
	m_info.SystemMemorySize = adapterDesc.SharedSystemMemory;

	// Query monitor outputs information.
	uint32 outputIndex = 0;
	RefCountPtr<IDXGIOutput> pOutput;
	while (D3D12_SUCCEED(m_adapter->EnumOutputs(outputIndex++, pOutput.ReleaseAndGetAddressOf())))
	{
		RefCountPtr<IDXGIOutput6> pOutput6;
		D3D12_VERIFY(D3D12Utils::As<IDXGIOutput6>(pOutput, &pOutput6));

		DXGI_OUTPUT_DESC1 outputDesc;
		pOutput6->GetDesc1(&outputDesc);

		auto& outputInfo = m_outputInfos.emplace_back();
		outputInfo.Name = CreateUTF8StringFromWide(outputDesc.DeviceName).data();
		outputInfo.Width = outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left;
		outputInfo.Height = outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top;
		outputInfo.ColorSpace = D3D12Types::ToRHI(outputDesc.ColorSpace);
		outputInfo.BitsPerColor = outputDesc.BitsPerColor;
		outputInfo.MinLuminance = outputDesc.MinLuminance;
		outputInfo.MaxLuminance = outputDesc.MaxLuminance;
		outputInfo.MaxFullFrameLuminance = outputDesc.MaxFullFrameLuminance;
	}
}

RefCountPtr<IDXGIFactory6> D3D12Adapter::GetFactory() const
{
	return m_pInstance->GetHandle();
}

void D3D12Adapter::EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos)
{
	if (!pOutputInfos)
	{
		outputCount = static_cast<uint32>(m_outputInfos.size());
		return;
	}

	for (uint32 outputIndex = 0; outputIndex < outputCount; ++outputIndex)
	{
		pOutputInfos[outputIndex] = &m_outputInfos[outputIndex];
	}
}

DeviceHandle D3D12Adapter::CreateDevice(const RHIDeviceCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Device>(this, createInfo);
}

void D3D12Adapter::SetType(const DXGI_ADAPTER_DESC3& desc)
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

}