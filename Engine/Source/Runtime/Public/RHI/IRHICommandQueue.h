#pragma once

#include <RHI/RHIEnums.h>

namespace ow
{

class IRHICommandQueue
{
public:
	virtual ~IRHICommandQueue() {}
	
	RHICommandType GetType() const { return m_commandQueueType; }

protected:
	void SetType(RHICommandType commandQueueType) { m_commandQueueType = commandQueueType; }
	
protected:
	RHICommandType m_commandQueueType;
};

}