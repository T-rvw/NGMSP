#pragma once

#include <optional>

namespace ow
{

inline constexpr std::nullopt_t NullOpt{ std::nullopt_t::_Tag{} };

template<typename T>
using Optional = std::optional<T>;

}