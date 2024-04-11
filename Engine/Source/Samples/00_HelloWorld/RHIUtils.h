#pragma once

#include <Core/HAL/BasicTypes.h>
#include <RHI/RHITypes.h>

#include <optional>
#include <vector>

namespace ow
{

class IRHIAdapter;

IRHIInstance* CreateRHIInstance(const RHIInstanceCreateInfo& createInfo);
std::optional<int32> FindBestRHIAdapter(const std::vector<IRHIAdapter*>& adapters);
std::optional<int32> FindBestCommandQueue(RHICommandType commandType, const std::vector<RHICommandQueueCreateInfo>& createInfos);
std::vector<RHICommandQueueCreateInfo> FindBestCommandQueues(const std::vector<RHICommandType>& commandTypes, const std::vector<RHICommandQueueCreateInfo>& createInfos);

void Dump(const IRHIInstance* pRHIInstance);
void Dump(const IRHIAdapter* pRHIAdapter);

}