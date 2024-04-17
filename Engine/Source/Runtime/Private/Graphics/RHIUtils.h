#pragma once

#include <RHI/RHITypes.h>

#include <optional>
#include <vector>

namespace ow
{

class IRHIAdapter;
class IRHIDevice;
class IRHIInstance;

class RHIUtils
{
public:
	static std::optional<int32> FindBestRHIAdapter(const std::vector<IRHIAdapter*>& adapters);
	static std::optional<int32> FindBestCommandQueue(RHICommandType commandType, const std::vector<RHICommandQueueCreateInfo*>& createInfos);
	static std::vector<RHICommandQueueCreateInfo*> FindBestCommandQueues(const std::vector<RHICommandType>& commandTypes, const std::vector<RHICommandQueueCreateInfo*>& createInfos);
};

}