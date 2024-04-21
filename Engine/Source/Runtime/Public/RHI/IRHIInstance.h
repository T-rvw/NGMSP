#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

enum class RHIBackend;

class IRHIAdapter;

class IRHIInstance : public RefCountObject
{
public:
	virtual ~IRHIInstance() {}
	
	virtual RHIBackend GetBackend() const = 0;
	virtual void EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters) = 0;
};

}