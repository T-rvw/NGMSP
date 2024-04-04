#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class RHIAdapter;

extern ENGINE_API RHIAdapter* FindBestRHIAdapter(std::vector<RHIAdapter>& adapters);

}