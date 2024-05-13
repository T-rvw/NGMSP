#pragma once

#include <Core/Math/Vector.hpp>

namespace ow
{

class XYZ : public Float3
{
public:
	using T = float;

public:
	using Float3::Float3;

	NODISCARD T Sum() const
	{
		T result = static_cast<T>(0);
		std::for_each(begin(), end(), [&result](const T& component) { result += component; });
		return result;
	}

	NODISCARD T Length() const { return std::sqrt(LengthSquare()); }
	NODISCARD T LengthSquare() const
	{
		T result = static_cast<T>(0);
		std::for_each(begin(), end(), [&result](const T& component) { result += component * component; });
		return result;
	}

	XYZ& Normalize()
	{
		T length = Length();
		if (Math::Equals(length, static_cast<T>(0)))
		{
			// avoid devide zero to cause nan.
			return *this;
		}

		T invLength = static_cast<T>(1) / length;
		std::for_each(begin(), end(), [&invLength](T& component) { component *= invLength; });
		return *this;
	}

	NODISCARD T Dot(const XYZ& other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z();
	}

	NODISCARD XYZ Cross(const XYZ& other) const
	{
		return XYZ(y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x());
	}
};

class XYZW : public XYZ
{
public:
	using T = XYZ::T;

public:
	constexpr XYZW() = default;
	explicit constexpr XYZW(const XYZ& v, T w) : XYZ(v.x(), v.y(), v.z()), m_w(w) {}
	explicit constexpr XYZW(T x, T y, T z, T w) : XYZ(x, y, z), m_w(w) {}

	constexpr T& w() { return m_w; }
	constexpr T w() const { return m_w; }

private:
	float m_w;
};

}