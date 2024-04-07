#pragma once

#include <RHI/RHITypes.h>

namespace ow
{

class RHIDevice;

class IRHIAdapter
{
public:
	virtual ~IRHIAdapter() {}

	virtual void Init() = 0;
	virtual void* GetHandle() const = 0;
	virtual std::vector<RHICommandQueueCreateInfo> QueryCommandQueueCreateInfos() = 0;
	virtual RHIDevice CreateDevice(const RHIDeviceCreateInfo& deviceCI, const std::vector<RHICommandQueueCreateInfo>& commandQueueCIs) const = 0;

	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }
	void SetName(std::string_view sv) { m_info.Name = sv; }
	void SetVendor(uint32 vendorID) { GetInfo().VendorID = vendorID; GetInfo().Vendor = GetGPUVendor(vendorID); }
	void SetDeviceID(uint32 deviceID) { GetInfo().DeviceID = deviceID; }
	void SetVideoMemorySize(uint64 memory) { m_info.VideoMemorySize = memory; }
	void SetSystemMemorySize(uint64 memory) { m_info.SystemMemorySize = memory; }
	void SetSharedMemorySize(uint64 memory) { m_info.SharedMemorySize = memory; }

private:
	RHIAdapterInfo m_info;
};

}