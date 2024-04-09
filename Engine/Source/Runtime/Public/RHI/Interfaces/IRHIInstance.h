#pragma once

#include <vector>

namespace ow
{

enum class RHIBackend;
struct RHIInstanceCreateInfo;

class RHIAdapter;
class RHISurface;

class IRHIInstance
{
public:
	virtual ~IRHIInstance() {}
	
	virtual void Init(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual RHIBackend GetBackend() const = 0;
	virtual void* GetHandle() const = 0;
	virtual std::vector<RHIAdapter> EnumerateAdapters() const = 0;
	virtual RHISurface CreateSurface(void* pPlatformWindowHandle, void* pPlatformInstanceHandle) const = 0;
};

}