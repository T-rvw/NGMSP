#pragma once

#include <Core/Base/NameOf.h>
#include <Core/Base/TypeTraits.h>

namespace ow
{

/// <summary>
/// Define bit flags in a safe way by using enum class.
/// </summary>
template<Enumerated T>
class BitFlags
{
private:
	using UT = std::underlying_type<T>::type;
	static constexpr auto BitFlagCount = EnumCount<T>();
	static_assert(BitFlagCount <= sizeof(UT) * 8);

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