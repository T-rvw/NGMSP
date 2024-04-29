#pragma once

#include <RHI/RHIFoward.h>

namespace ow
{

class IRHIInstance : public RefCountObject
{
public:
	virtual ~IRHIInstance() {}
	
	virtual RHIBackend GetBackend() const = 0;
	virtual void EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters) = 0;
};

}