#pragma once

#include <RHI/RHIFoward.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIBuffer : public RefCountObject
{
public:
	virtual ~IRHIBuffer() {}

	const RHIBufferCreateInfo& GetCreateInfo() const { return m_bufferCreateInfo; }

protected:
	RHIBufferCreateInfo m_bufferCreateInfo;
};

}