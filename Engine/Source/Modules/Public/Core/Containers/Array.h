#pragma once

#include <Core/HAL/BasicTypes.h>

#include <array>

namespace ow
{

template<typename T, uint32 N>
using Array = std::array<T, N>;

}