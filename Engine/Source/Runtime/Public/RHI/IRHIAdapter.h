#pragma once

#include <RHI/RHIFoward.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIAdapter
{
public:
	virtual ~IRHIAdapter() {}

	virtual void EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos) = 0;
	virtual DeviceHandle CreateDevice(const RHIDeviceCreateInfo& createInfo) = 0;

	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }

protected:
	RHIAdapterInfo m_info;
};

}