#pragma once

#include <memory>
#include <vector>

namespace ow
{

struct RHIInstanceCreateInfo;

class RHIAdapter;

class IRHIInstance
{
public:
	virtual void Init(const RHIInstanceCreateInfo& createInfo) = 0;

	virtual void* GetHandle() const = 0;

	virtual std::vector<std::unique_ptr<RHIAdapter>> EnumAdapters() = 0;
};

}