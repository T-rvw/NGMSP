#pragma once

#include <Core/Math/Vector.hpp>

namespace ow
{

template<typename T>
class TRay
{
public:
	constexpr TRay() = default;
	explicit constexpr TRay(Float3 origin, Float3 direction) : m_origin(MoveTemp(origin)), m_direction(MoveTemp(direction)) {}
	TRay(const TRay& other) = default;
	TRay& operator=(const TRay& other) = default;
	TRay(TRay&& other) = default;
	TRay& operator=(TRay&& other) = default;
	~TRay() = default;

	bool IsValid() const { return !m_direction.Equals(0.0f); }
	Float3 GetPointAt(T parameter) const { return m_origin + m_direction * parameter; }
	T GetParameter(const Float3& point) const { return (point - m_origin).Dot(m_direction); }
	const Float3& GetDirection() const { return m_direction; }
	const Float3& GetOrigin() const { return m_origin; }

private:
	Float3 m_origin;
	Float3 m_direction;
};

using Ray = TRay<float>;

static_assert(6 * sizeof(float) == sizeof(Ray));

}