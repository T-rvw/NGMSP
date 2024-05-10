#pragma once

#include <Core/Base/Assert.h>
#include <Core/Base/TypeTraits.h>

namespace ow
{

// std::forward
template<typename T>
[[nodiscard]] constexpr T&& Forward(std::remove_reference_t<T>& value)
{
	return static_cast<T&&>(value);
}

template<typename T>
[[nodiscard]] constexpr T&& Forward(std::remove_reference_t<T>&& value)
{
	return static_cast<T&&>(value);
}

// std::move is only valid for lvalue and non-const objects, but no compiler warnings if you make mistakes.
// MoveTemp will validate in compile time to avoid possible performance loss.
template<typename T>
[[nodiscard]] constexpr std::remove_reference_t<T>&& MoveTemp(T&& value) noexcept
{
	using CastType = std::remove_reference_t<T>;
	static_assert(std::is_lvalue_reference_v<T>, "T is lvalue reference object.");
	static_assert(!std::is_same_v<CastType&, const CastType&>, "For a const object, MoveTemp doesn't take effect.");
	return static_cast<CastType&&>(value);
}

}