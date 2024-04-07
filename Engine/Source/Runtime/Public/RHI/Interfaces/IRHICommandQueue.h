#pragma once

#include <RHI/RHIEnums.h>

namespace ow
{

class IRHICommandQueue
{
public:
	virtual ~IRHICommandQueue() {}
	
	virtual void Init() = 0;
	virtual void* GetHandle() const = 0;

	void SetType(RHICommandQueueType commandQueueType) { m_commandQueueType = commandQueueType; }
	RHICommandQueueType GetType() const { return m_commandQueueType; }

private:
	RHICommandQueueType m_commandQueueType;
};

}