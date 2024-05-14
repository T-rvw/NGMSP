#pragma once

#include <Core/Math/Math.hpp>

namespace ow
{

template<Numeric T, uint32 N>
class TVector
{
public:
	constexpr TVector() = default;
	// N value constructor.
	template <typename... Args>
	explicit constexpr TVector(Args... args) :
		m_data { static_cast<T>(args)... }
	{
		static_assert(sizeof...(Args) == N);
	}
	TVector(const TVector&) = default;
	TVector& operator=(const TVector&) = default;
	TVector(TVector&&) = default;
	TVector& operator=(TVector&&) = default;
	~TVector() = default;

	T* begin() { return &m_data[0]; }
	const T* begin() const { return &m_data[0]; }
	T* end() { return &m_data[0] + N; }
	const T* end() const { return &m_data[0] + N; }
	constexpr uint32 size() const { return N; }

	constexpr T& operator[](uint32 index) { return m_data[index]; }
	constexpr T operator[](uint32 index) const { return m_data[index]; }

	NODISCARD bool ContainsInfinite() const
	{
		for (uint32 index = 0; index < N; ++index)
		{
			if (std::isfinite(m_data[index]))
			{
				return true;
			}
		}

		return false;
	}

	NODISCARD bool ContainsNan() const
	{
		for (uint32 index = 0; index < N; ++index)
		{
			if (std::isnan(m_data[index]))
			{
				return true;
			}
		}

		return false;
	}

	NODISCARD bool Contains(T value) const
	{
		for (uint32 index = 0; index < N; ++index)
		{
			if (Math::Equals(m_data[index], value))
			{
				return true;
			}
		}

		return false;
	}

	NODISCARD bool Equals(const TVector& other) const
	{
		for (uint32 index = 0; index < N; ++index)
		{
			if (!Math::Equals(m_data[index], other[index]))
			{
				return false;
			}
		}

		return true;
	}

	bool operator!=(const TVector& other) const { return !Equals(other); }
	bool operator==(const TVector& other) const { return Equals(other); }

	NODISCARD TVector operator+(const TVector& other) const { return TVector(*this) += other; }
	TVector& operator+=(const TVector& other)
	{
		int32 count = 0;
		std::for_each(begin(), end(), [&other, &count](T& component) { component += other[count++]; });
		return *this;
	}

	NODISCARD TVector operator-(const TVector& other) const { return TVector(*this) -= other; }
	TVector& operator-=(const TVector& other)
	{
		int count = 0;
		std::for_each(begin(), end(), [&other, &count](T& component) { component -= other[count++]; });
		return *this;
	}

	NODISCARD friend TVector operator*(T lhs, const TVector& other) { return other * lhs; }
	TVector operator*(T value) const { return TVector(*this) *= value; }
	TVector& operator*=(T value)
	{
		std::for_each(begin(), end(), [&value](T& component) { component *= value; });
		return *this;
	}
	NODISCARD TVector operator*(const TVector& other) const { return TVector(*this) *= other; }
	TVector& operator*=(const TVector& other)
	{
		int count = 0;
		std::for_each(begin(), end(), [&other, &count](T& component) { component *= other[count++]; });
		return *this;
	}

	NODISCARD TVector operator/(T value) const { return TVector(*this) /= value; }
	TVector& operator/=(T value)
	{
		std::for_each(begin(), end(), [&value](T& component) { component /= value; });
		return *this;
	}
	NODISCARD TVector operator/(const TVector& other) const { return TVector(*this) /= other; }
	TVector& operator/=(const TVector& other)
	{
		int count = 0;
		std::for_each(begin(), end(), [&other, &count](T& component) { component /= other[count++]; });
		return *this;
	}

protected:
	T m_data[N];
};

template<typename T>
class Vector2 : public TVector<T, 2>
{
public:
	using Base = TVector<T, 2>;

public:
	constexpr Vector2() = default;
	explicit constexpr Vector2(T value) { std::fill(this->begin(), this->end(), value); }
	explicit constexpr Vector2(T x, T y) : Base(x, y) {}

	constexpr T& x() { return this->m_data[0]; }
	constexpr T x() const { return this->m_data[0]; }
	constexpr T& y() { return this->m_data[1]; }
	constexpr T y() const { return this->m_data[1]; }
};

template<typename T>
class Vector3 : public TVector<T, 3>
{
public:
	using Base = TVector<T, 3>;
	using Vector2 = TVector<T, 2>;

public:
	constexpr Vector3() = default;
	explicit constexpr Vector3(T value) { std::fill(this->begin(), this->end(), value); }
	explicit constexpr Vector3(const Vector2& v, T z) : Base(v.x, v.y, z) {}
	explicit constexpr Vector3(T x, T y, T z) : Base(x, y, z) {}

	constexpr T& x() { return this->m_data[0]; }
	constexpr T x() const { return this->m_data[0]; }
	constexpr T& y() { return this->m_data[1]; }
	constexpr T y() const { return this->m_data[1]; }
	constexpr T& z() { return this->m_data[2]; }
	constexpr T z() const { return this->m_data[2]; }

	NODISCARD T Sum() const
	{
		T result = static_cast<T>(0);
		std::for_each(this->begin(), this->end(), [&result](const T& component) { result += component; });
		return result;
	}

	NODISCARD T Length() const { return std::sqrt(LengthSquare()); }
	NODISCARD T LengthSquare() const
	{
		T result = static_cast<T>(0);
		std::for_each(this->begin(), this->end(), [&result](const T& component) { result += component * component; });
		return result;
	}

	Vector3& Normalize()
	{
		T length = Length();
		if (Math::Equals(length, static_cast<T>(0)))
		{
			// avoid devide zero to cause nan.
			return *this;
		}

		T invLength = static_cast<T>(1) / length;
		std::for_each(this->begin(), this->end(), [&invLength](T& component) { component *= invLength; });
		return *this;
	}

	NODISCARD T Dot(const Vector3& other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z();
	}

	NODISCARD Vector3 Cross(const Vector3& other) const
	{
		return Vector3(y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x());
	}
};

template<typename T>
class Vector4 : public Vector3<T>
{
public:
	using Base = TVector<T, 4>;
	using Vector3 = Vector3<T>;

public:
	constexpr Vector4() = default;
	explicit constexpr Vector4(const Vector3& v, T w) : Vector3(v.x(), v.y(), v.z()), m_w(w) {}
	explicit constexpr Vector4(T x, T y, T z, T w) : Vector3(x, y, z), m_w(w) {}

	constexpr T& w() { return m_w; }
	constexpr T w() const { return m_w; }

private:
	T m_w;
};

using Int2 = Vector2<int32>;
using Int3 = Vector3<int32>;
using Int4 = Vector4<int32>;
static_assert(2 * sizeof(int32) == sizeof(Int2));
static_assert(3 * sizeof(int32) == sizeof(Int3));
static_assert(4 * sizeof(int32) == sizeof(Int4));

using UInt2 = Vector2<uint32>;
using UInt3 = Vector3<uint32>;
using UInt4 = Vector4<uint32>;
static_assert(2 * sizeof(uint32) == sizeof(UInt2));
static_assert(3 * sizeof(uint32) == sizeof(UInt3));
static_assert(4 * sizeof(uint32) == sizeof(UInt4));

using Float2 = Vector2<float>;
using Float3 = Vector3<float>;
using Float4 = Vector4<float>;
static_assert(2 * sizeof(float) == sizeof(Float2));
static_assert(3 * sizeof(float) == sizeof(Float3));
static_assert(4 * sizeof(float) == sizeof(Float4));

using Double2 = Vector2<double>;
using Double3 = Vector3<double>;
using Double4 = Vector4<double>;
static_assert(2 * sizeof(double) == sizeof(Double2));
static_assert(3 * sizeof(double) == sizeof(Double3));
static_assert(4 * sizeof(double) == sizeof(Double4));

}