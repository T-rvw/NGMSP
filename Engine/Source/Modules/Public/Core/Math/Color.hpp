#pragma once

#include <Core/Math/Vector.hpp>

namespace ow
{

template<typename T>
class TColor : public TVector<T, 4>
{
public:
	using Base = TVector<T, 4>;

public:
	constexpr TColor() = default;
	explicit constexpr TColor(T r, T g, T b, T a) : Base(r, g, b, a) {}

	constexpr T& r() { return this->m_data[0]; }
	constexpr T r() const { return this->m_data[0]; }
	constexpr T& g() { return this->m_data[1]; }
	constexpr T g() const { return this->m_data[1]; }
	constexpr T& b() { return this->m_data[2]; }
	constexpr T b() const { return this->m_data[2]; }
	constexpr T& a() { return this->m_data[3]; }
	constexpr T a() const { return this->m_data[3]; }
};

class Color : public TColor<uint8>
{
public:
	using T = uint8;
	using Base = TColor<uint8>;

public:
	using Base::Base;
	explicit constexpr Color(T r, T g, T b) : Base(r, g, b, 255) {}

	constexpr uint32 ToARGB() const
	{
		return (a() << 24) | (r() << 16) | (g() << 8) | (b() << 0);
	}

	constexpr uint32 ToABGR() const
	{
		return (a() << 24) | (b() << 16) | (g() << 8) | (r() << 0);
	}

	constexpr uint32 ToRGBA()
	{
		return (r() << 24) | (g() << 16) | (b() << 8) | (a() << 0);
	}

	constexpr uint32 ToBGRA() const
	{
		return (b() << 24) | (g() << 16) | (r() << 8) | (a() << 0);
	}
};

static_assert(4 * sizeof(uint8) == sizeof(Color));

class LinearColor : public TColor<float>
{
public:
	using T = uint8;
	using Base = TColor<float>;

public:
	using Base::Base;
	explicit constexpr LinearColor(T r, T g, T b) : Base(r, g, b, 1.0f) {}
};

static_assert(4 * sizeof(float) == sizeof(LinearColor));

}