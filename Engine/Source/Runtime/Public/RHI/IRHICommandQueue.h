#pragma once

#include <RHI/RHIEnums.h>

namespace ow
{

class IRHICommandQueue
{
public:
	virtual ~IRHICommandQueue() {}
	
	virtual void* GetHandle() const = 0;

	void SetType(RHICommandType commandQueueType) { m_commandQueueType = commandQueueType; }
	RHICommandType GetType() const { return m_commandQueueType; }

private:
	RHICommandType m_commandQueueType;
};

}