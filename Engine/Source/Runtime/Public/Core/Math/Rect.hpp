#pragma once

#include <Core/Math/Vector.hpp>

namespace ow
{

template<typename T>
class TRect
{
public:
	using Point = TVector<T, 2>;

public:
	TRect() = default;
	explicit TRect(T left, T top, T right, T bottom) :
		m_leftTop(left, top), m_rightBottom(right, bottom)
	{
	}
	explicit TRect(T width, T height) :
		m_leftTop(static_cast<T>(0), static_cast<T>(0)), m_rightBottom(width, height)
	{
	}
	explicit TRect(Point leftTop, Point rightBottom) :
		m_leftTop(MoveTemp(leftTop)), m_rightBottom(MoveTemp(rightBottom))
	{
	}
	TRect(const TRect& other) = default;
	TRect& operator=(const TRect& other) = default;
	TRect(TRect&& other) = default;
	TRect& operator=(TRect&& other) = default;
	~TRect() = default;

	const Point& GetLeftTop() const { return m_leftTop; }
	const Point& GetBottomRight() const { return m_rightBottom; }

	T GetLeft() const { return m_leftTop[0]; }
	T GetTop() const { return m_leftTop[1]; }
	T GetRight() const { return m_rightBottom[0]; }
	T GetBottom() const { return m_rightBottom[1]; }
	T GetWidth() const { return m_rightBottom[0] - m_leftTop[0]; }
	T GetHeight() const { return m_rightBottom[1] - m_leftTop[1]; }

private:
	Point m_leftTop;
	Point m_rightBottom;
};

using Rect = TRect<int32>;

}