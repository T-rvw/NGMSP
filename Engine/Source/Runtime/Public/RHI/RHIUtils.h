#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class RHIAdapter;

extern ENGINE_API RHIAdapter* FindBestRHIAdapter(const std::vector<std::unique_ptr<RHIAdapter>>& adapters);

}