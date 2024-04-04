#pragma once

#include <memory>
#include <vector>

namespace ow
{

enum class RHIBackend;
struct RHIInstanceCreateInfo;

class RHIAdapter;

class IRHIInstance
{
public:
	virtual void Init(const RHIInstanceCreateInfo& createInfo) = 0;
	virtual ~IRHIInstance() {}

	virtual RHIBackend GetBackend() const = 0;
	virtual void* GetHandle() const = 0;

	virtual std::vector<RHIAdapter> EnumAdapters() const = 0;
};

}