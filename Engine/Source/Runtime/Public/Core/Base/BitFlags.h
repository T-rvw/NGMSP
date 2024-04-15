#pragma once

#include <type_traits>

namespace ow
{

/// <summary>
/// Define bit flags in a safe way by using enum class.
/// </summary>
/// <typeparam name="T">Type of enum class</typeparam>
template<typename T>
class BitFlags
{
private:
	static_assert(std::is_enum<T>::value);
	using UT = std::underlying_type<T>::type;

	static constexpr UT GetFlag(T v)
	{
		return static_cast<UT>(1) << static_cast<UT>(v);
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

	constexpr BitFlags(UT v) :
		m_flags(v)
	{
	}

	constexpr BitFlags<T> operator|(T v) const
	{
		return BitFlags<T>(m_flags | GetFlag(v));
	}

	constexpr BitFlags<T>& operator|=(T v)
	{
		m_flags |= GetFlag(v);
		return *this;
	}

	constexpr BitFlags<T>& Enable(T v)
	{
		m_flags |= GetFlag(v);
		return *this;
	}

	constexpr bool operator&(T v) const
	{
		return m_flags & GetFlag(v);
	}

	constexpr bool IsEnabled(T v) const
	{
		return m_flags & GetFlag(v);
	}

private:
	UT m_flags;
};

}