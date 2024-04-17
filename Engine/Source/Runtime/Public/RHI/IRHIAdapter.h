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

	virtual void Initialize() = 0;
	virtual void EnumerateCommandQueues(uint32& queueCICount, RHICommandQueueCreateInfo** pCommandQueueCIs) = 0;

	RHIAdapterInfo& GetInfo() { return m_info; }
	const RHIAdapterInfo& GetInfo() const { return m_info; }

protected:
	RHIAdapterInfo m_info;
};

}