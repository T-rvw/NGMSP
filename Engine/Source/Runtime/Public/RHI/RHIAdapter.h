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

	void Init(std::unique_ptr<IRHIAdapter> impl);
	void Dump();

	GPUAdapterType GetType() const;
	GPUVendor GetVendor() const;
	uint64 GetVideoMemorySize() const;
	uint64 GetSystemMemorySize() const;
	uint64 GetSharedMemorySize() const;
	const char* GetName() const;

	std::unique_ptr<RHIDevice> CreateDevice(const RHIDeviceCreateInfo& createInfo) const;

private:
	IRHIAdapter* m_pImpl = nullptr;
};

}