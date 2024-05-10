#pragma once

#include <Core/Math/Math.hpp>

namespace ow
{

template<typename T, uint32 N>
class TVector
{
public:
	constexpr TVector() = default;
	// Single value constructor.
	explicit constexpr TVector(T value) { std::fill(begin(), end(), value); }
	// N value constructor.
	template <typename... Args>
	explicit constexpr TVector(Args... args) :
		m_data { static_cast<T>(args)... }
	{
		static_assert(sizeof...(Args) == N);
	}
	// N-1 TVector + 1 value constructor.
	explicit constexpr TVector(TVector<T, N - 1> vec, T value)
	{
		std::memcpy(begin(), vec.begin(), sizeof(T) * vec.size());
		m_data[N - 1] = value;
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
	constexpr T& x() { static_assert(N >= 1); return m_data[0]; }
	constexpr T x() const { static_assert(N >= 1); return m_data[0]; }
	constexpr T& y() { static_assert(N >= 2); return m_data[1]; }
	constexpr T y() const { static_assert(N >= 2); return m_data[1]; }
	constexpr T& z() { static_assert(N >= 3); return m_data[2]; }
	constexpr T z() const { static_assert(N >= 3); return m_data[2]; }
	constexpr T& w() { static_assert(N >= 4); return m_data[3]; }
	constexpr T w() const { static_assert(N >= 4); return m_data[3]; }
	NODISCARD constexpr TVector<T, 3> xxx() const { static_assert(3 <= N); return TVector<T, 3>(x()); }
	NODISCARD constexpr TVector<T, 3> yyy() const { static_assert(3 <= N); return TVector<T, 3>(y()); }
	NODISCARD constexpr TVector<T, 3> zzz() const { static_assert(3 <= N); return TVector<T, 3>(z()); }
	NODISCARD constexpr TVector<T, 3> xyz() const { static_assert(3 <= N); return TVector<T, 3>(x(), y(), z()); }

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

	TVector& Normalize()
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

	NODISCARD T Dot(const TVector& other) const
	{
		static_assert(N >= 3);
		return x() * other.x() + y() * other.y() + z() * other.z();
	}

	NODISCARD TVector<T, 3> Cross(const TVector& other) const
	{
		static_assert(N >= 3);
		return TVector<T, 3>(y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x());
	}

private:
	T m_data[N];
};

using Vec2 = TVector<float, 2>;
using Vec3 = TVector<float, 3>;
using Vec4 = TVector<float, 4>;

}