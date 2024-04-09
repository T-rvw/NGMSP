#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class RHIAdapter;

extern ENGINE_API std::optional<int32> FindBestRHIAdapter(const std::vector<RHIAdapter>& adapters);
extern ENGINE_API std::optional<int32> FindBestCommandQueue(RHICommandType commandType, const std::vector<RHICommandQueueCreateInfo>& createInfos);
extern ENGINE_API std::vector<RHICommandQueueCreateInfo> FindBestCommandQueues(const std::vector<RHICommandType>& commandTypes, const std::vector<RHICommandQueueCreateInfo>& createInfos);

}