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
	void SetVRAMSize(uint64 vram) { m_info.VRAMSize = vram; }
	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }

private:
	RHIAdapterInfo m_info;
};

}