#pragma once

#include <Core/HAL/BasicTypes.h>

#include <nameof/nameof.hpp>

namespace ow
{

template <typename E>
[[nodiscard]] constexpr int32 EnumCount() noexcept
{
	return nameof::detail::count_v<std::decay_t<E>>;
}

template <typename E>
[[nodiscard]] constexpr auto EnumName(E value) noexcept
{
	return nameof::nameof_enum(value);
}

}