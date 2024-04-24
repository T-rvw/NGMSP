#pragma once

#include <Core/Base/RefCountPtr.h>

#include <RHI/RHITypes.h>

namespace ow
{

struct RHIDeviceCreateInfo;

class IRHIDevice;

class IRHIAdapter
{
public:
	virtual ~IRHIAdapter() {}

	virtual void Init() = 0;
	virtual void EnumerateOutputs(uint32& outputCount, RHIOutputInfo** pOutputInfos) = 0;
	virtual void EnumerateCommandQueues(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs) = 0;
	virtual RefCountPtr<IRHIDevice> CreateDevice(const RHIDeviceCreateInfo& createInfo) = 0;

	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }

protected:
	RHIAdapterInfo m_info;
};

}