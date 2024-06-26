#pragma once

#include <Core/Math/Vector.hpp>

namespace ow
{

/// <summary>
/// Presents generic box type. N means dimensions.
/// </summary>
template<Numeric T, uint32 N>
class TBox
{
public:
	using PointType = TVector<T, N>;

public:
	explicit constexpr TBox() = default;

	explicit constexpr TBox(PointType min, PointType max)
		: m_min(MoveTemp(min)), m_max(MoveTemp(max))
	{
	}

	explicit constexpr TBox(T min, T max) : TBox(PointType(min), PointType(max))
	{
	}

	TBox(const TBox&) = default;
	TBox& operator=(const TBox&) = default;
	TBox(TBox&&) = default;
	TBox& operator=(TBox&&) = default;
	~TBox() = default;

	PointType& Min() { return m_min; }
	PointType& Max() { return m_max; }
	const PointType& Min() const { return m_min; }
	const PointType& Max() const { return m_max; }
	PointType Center() const { return m_min + (m_max - m_min) * static_cast<T>(0.5); }
	PointType Size() const { return m_max - m_min; }

	bool Empty() const { return m_min == m_max; }
	bool IsPointInside(const PointType& point) const
	{
		for (size_t dimensionIndex = 0; dimensionIndex < N; ++dimensionIndex)
		{
			if (point[dimensionIndex] < m_min[dimensionIndex] ||
				point[dimensionIndex] > m_max[dimensionIndex])
			{
				return false;
			}
		}

		return true;
	}

	void Merge(const TBox& other)
	{
		for (size_t dimensionIndex = 0; dimensionIndex < N; ++dimensionIndex)
		{
			m_min[dimensionIndex] = std::min<T>(m_min[dimensionIndex], other.Min()[dimensionIndex]);
			m_max[dimensionIndex] = std::max<T>(m_max[dimensionIndex], other.Max()[dimensionIndex]);
		}
	}

	bool Intersects(const TBox& other) const
	{
		for (uint32_t index = 0U; index < N; ++index)
		{
			if (other.Max()[index] < m_min[index] || other.Min()[index] > m_max[index])
			{
				return false;
			}
		}

		return true;
	}

	TBox GetIntersection(const TBox& other) const
	{
		constexpr T zero = static_cast<T>(0);

		TVector<T, N> min(zero);
		TVector<T, N> max(zero);
		for (uint32_t index = 0U; index < N; ++index)
		{
			min[index] = std::max(m_min[index], other.Min()[index]);
			max[index] = std::min(m_max[index], other.Max()[index]);
		}
		return TBox(MoveTemp(min), MoveTemp(max));
	}

protected:
	PointType m_min;
	PointType m_max;
};

/// <summary>
/// 2D Rect such as GUI Window Rect, 3D viewport, scissor.
/// </summary>
template<typename T>
class TRect : public TBox<T, 2>
{
public:
	using Base = TBox<T, 2>;
	using PointType = Base::PointType;

public:
	constexpr TRect() = default;
	explicit constexpr TRect(T width, T height) :
		Base(PointType(static_cast<T>(0), static_cast<T>(0)), PointType(width, height))
	{
	}
	explicit constexpr TRect(T left, T top, T right, T bottom) :
		Base(PointType(left, top), PointType(right, bottom))
	{
	}

	PointType& GetLeftTop() { return this->m_min; }
	const PointType& GetLeftTop() const { return this->m_min; }
	PointType& GetBottomRight() { return this->m_max; }
	const PointType& GetBottomRight() const { return this->m_max; }

	constexpr T GetLeft() const { return this->m_min[0]; }
	constexpr T GetTop() const { return this->m_min[1]; }
	constexpr T GetRight() const { return this->m_max[0]; }
	constexpr T GetBottom() const { return this->m_max[1]; }
	constexpr T GetWidth() const { return this->m_max[0] - this->m_min[0]; }
	constexpr T GetHeight() const { return this->m_max[1] - this->m_min[1]; }
};

using Rect = TRect<uint32>;
static_assert(sizeof(Rect) == 4 * sizeof(uint32));

/// <summary>
/// Viewport inherited from Rect which adds MinDepth and MaxDepth.
/// </summary>
template<typename T>
class TViewport : public TRect<T>
{
public:
	using Base = TRect<T>;

public:
	using Base::Base;

	constexpr T GetMinDepth() const { return m_minDepth; }
	void SetMinDepth(T depth) { m_minDepth = depth; }

	constexpr T GetMaxDepth() const { return m_maxDepth; }
	void SetMaxDepth(T depth) { m_maxDepth = depth; }

private:
	T m_minDepth;
	T m_maxDepth;
};

using Viewport = TViewport<float>;
static_assert(6 * sizeof(float) == sizeof(Viewport));

/// <summary>
/// Axis Aligned Bounding Box.
/// </summary>
template<typename T>
class TAABB : public TBox<T, 3>
{
public:
	using Base = TBox<T, 3>;

public:
	using Base::Base;
};

using AABB = TAABB<float>;
static_assert(6 * sizeof(float) == sizeof(AABB));

}