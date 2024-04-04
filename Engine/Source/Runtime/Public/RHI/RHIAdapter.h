#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHIDevice.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIAdapter;

/// <summary>
/// RHIAdapter is a physcial device which helps to query device details before creating logical devices.
/// Vulkan : VkPhyscialDevice
/// D3D12 : IDXGIAdapter(n)
/// Metal : MTLDevice
/// </summary>
class RHI_API RHIAdapter
{
public:
	RHIAdapter();
	explicit RHIAdapter(std::unique_ptr<IRHIAdapter> impl);
	RHIAdapter(const RHIAdapter&) = delete;
	RHIAdapter& operator=(const RHIAdapter&) = delete;
	RHIAdapter(RHIAdapter&& other) noexcept;
	RHIAdapter& operator=(RHIAdapter&& other) noexcept;
	~RHIAdapter();

	void Init();
	void Reset(std::unique_ptr<IRHIAdapter> impl);
	void Dump() const;

	GPUAdapterType GetType() const;
	GPUVendor GetVendor() const;
	uint32 GetVendorID() const;
	uint32 GetDeviceID() const;
	uint64 GetVideoMemorySize() const;
	uint64 GetSystemMemorySize() const;
	uint64 GetSharedMemorySize() const;
	const char* GetName() const;

	RHIDevice CreateDevice(const RHIDeviceCreateInfo& createInfo) const;

private:
	IRHIAdapter* m_pImpl = nullptr;
};

}