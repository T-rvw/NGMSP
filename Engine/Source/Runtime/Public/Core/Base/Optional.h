#pragma once

#include <Core/HAL/CompilerDefines.h>

#include <optional>

namespace ow
{

INLINE constexpr std::nullopt_t NullOpt{ std::nullopt_t::_Tag{} };

template<typename T>
using Optional = std::optional<T>;

}