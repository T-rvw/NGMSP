#pragma once

#include <Core/Base/Assert.h>
#include <Core/HAL/CompilerDefines.h>

#include <type_traits>

namespace ow
{

// Concepts
template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <typename T>
concept Numeric = Integral<T> || FloatingPoint<T>;

template <typename T>
concept Enumerated = std::is_enum_v<T>;

template <typename T>
concept Trivial = std::is_trivial_v<T>;

// std::forward
template<typename T>
NODISCARD constexpr T&& Forward(std::remove_reference_t<T>& value)
{
	return static_cast<T&&>(value);
}

template<typename T>
NODISCARD constexpr T&& Forward(std::remove_reference_t<T>&& value)
{
	return static_cast<T&&>(value);
}

// std::move is only valid for lvalue and non-const objects, but no compiler warnings if you make mistakes.
// MoveTemp will validate in compile time to avoid possible performance loss.
template<typename T>
NODISCARD constexpr std::remove_reference_t<T>&& MoveTemp(T&& value) noexcept
{
	using CastType = std::remove_reference_t<T>;
	static_assert(std::is_lvalue_reference_v<T>, "T is lvalue reference object.");
	static_assert(!std::is_same_v<CastType&, const CastType&>, "For a const object, MoveTemp doesn't take effect.");
	return static_cast<CastType&&>(value);
}

}