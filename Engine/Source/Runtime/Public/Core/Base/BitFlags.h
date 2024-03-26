#pragma once

#include <Core/HAL/APIDefinition.h>

#include <type_traits>

namespace ow
{

/// <summary>
/// Helps to define bit flags in a safe way by using enum class.
/// </summary>
/// <typeparam name="T">Type of enum class</typeparam>
template<typename T>
class ENGINE_API BitFlags
{
private:
	static_assert(std::is_enum<T>::value);
	using UT = std::underlying_type<T>::type;

	static constexpr UT GetFlag(T v)
	{
		return 1 << static_cast<UT>(v);
	}

public:
	constexpr BitFlags() :
		m_flags(static_cast<UT>(0))
	{
	}

	constexpr BitFlags(T v) :
		m_flags(GetFlag(v))
	{
	}

	constexpr BitFlags operator|(T v) const
	{
		return BitFlags(m_flags | GetFlag(v));
	}

	constexpr BitFlags& operator|=(T v)
	{
		m_flags |= GetFlag(v);
		return *this;
	}

	constexpr bool operator&(T v) const
	{
		return m_flags & GetFlag(v);
	}

private:
	UT m_flags;
};

template<typename T>
constexpr BitFlags<T> operator|(T lhs, T rhs)
{
	return BitFlags<T>(lhs) | rhs;
}

}