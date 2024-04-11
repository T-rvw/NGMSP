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
	
	virtual void Init(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual RHIBackend GetBackend() const = 0;
	virtual void* GetHandle() const = 0;
	virtual std::vector<IRHIAdapter*> EnumerateAdapters() const = 0;
};

}