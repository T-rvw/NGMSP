#pragma once

#include <vector>

namespace ow
{

enum class RHIBackend;
struct RHIInstanceCreateInfo;

class IRHIAdapter;

class IRHIInstance
{
public:
	virtual ~IRHIInstance() {}
	
	virtual RHIBackend GetBackend() const = 0;
	virtual void Init(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual void EnumerateAdapters(uint32& adapterCount, IRHIAdapter** pAdapters) = 0;
};

}