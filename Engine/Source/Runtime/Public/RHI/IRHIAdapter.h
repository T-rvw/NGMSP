#pragma once

#include <Core/HAL/BasicTypes.h>
#include <RHI/RHITypes.h>

#include <vector>

namespace ow
{

class IRHIDevice;

class IRHIAdapter
{
public:
	virtual ~IRHIAdapter() {}

	virtual void Init() = 0;
	virtual void* GetHandle() const = 0;
	virtual std::vector<RHICommandQueueCreateInfo> QueryCommandQueueCreateInfos() = 0;
	virtual IRHIDevice* CreateDevice(const RHIDeviceCreateInfo& deviceCI, const std::vector<RHICommandQueueCreateInfo>& commandQueueCIs) const = 0;

	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }

protected:
	RHIAdapterInfo m_info;
};

}