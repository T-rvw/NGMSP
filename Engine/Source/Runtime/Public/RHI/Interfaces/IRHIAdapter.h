#pragma once

#include <RHI/RHITypes.h>

namespace ow
{

class IRHIAdapter
{
public:
	virtual void Init() = 0;
	virtual void* GetHandle() const = 0;
	virtual ~IRHIAdapter() {}

	void SetName(std::string_view sv) { m_info.Name = sv; }
	void SetVendor(uint32 vendorID) { GetInfo().Vendor = GetGPUVendor(vendorID); }
	void SetVideoMemorySize(uint64 memory) { m_info.VideoMemorySize = memory; }
	void SetSystemMemorySize(uint64 memory) { m_info.SystemMemorySize = memory; }
	void SetSharedMemorySize(uint64 memory) { m_info.SharedMemorySize = memory; }
	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }

private:
	RHIAdapterInfo m_info;
};

}