#pragma once

#include <Core/Math/Matrix.hpp>
#include <Core/Math/Quaternion.hpp>

namespace ow
{

template<typename T>
class TTransform final
{
public:
	using ValueType = T;
	static constexpr std::size_t Size = 10;
	using Iterator = T*;
	using ConstIterator = const T*;

	static TTransform Identity() { return TTransform(TVector<T, 3>::Zero(), TQuaternion<T>::Identity(), TVector<T, 3>::One()); }

public:
	TTransform() = default;

	TTransform(TVector<T, 3> translation, TQuaternion<T> rotation, TVector<T, 3> scale) :
		m_translation(cd::MoveTemp(translation)),
		m_rotation(cd::MoveTemp(rotation)),
		m_scale(cd::MoveTemp(scale))
	{
	}

	TTransform(const TTransform&) = default;
	TTransform& operator=(const TTransform&) = default;
	TTransform(TTransform&&) = default;
	TTransform& operator=(TTransform&&) = default;
	~TTransform() = default;

	void Clear()
	{
		m_translation.Set(static_cast<T>(0));
		m_rotation.Clear();
		m_scale.Set(static_cast<T>(1));
	}

	// Get
	Iterator begin() { return &m_translation[0]; }
	Iterator end() { return &m_translation[0] + Size; }
	ConstIterator begin() const { return &m_translation[0]; }
	ConstIterator end() const { return &m_translation[0] + Size; }

	void SetTranslation(TVector<T, 3> translation) { m_translation = cd::MoveTemp(translation); }
	TVector<T, 3>& GetTranslation() { return m_translation; }
	const TVector<T, 3>& GetTranslation() const { return m_translation; }

	void SetRotation(TQuaternion<T> rotation) { m_rotation = cd::MoveTemp(rotation); }
	TQuaternion<T>& GetRotation() { return m_rotation; }
	const TQuaternion<T>& GetRotation() const { return m_rotation; }

	void SetScale(TVector<T, 3> scale) { m_scale = cd::MoveTemp(scale); }
	TVector<T, 3>& GetScale() { return m_scale; }
	const TVector<T, 3>& GetScale() const { return m_scale; }

	TMatrix<T, 4, 4> GetMatrix() const
	{
		TMatrix<T, 4, 4> rotation = m_rotation.ToMatrix4x4();

		// Apply translation.
		rotation.GetColumn(3)[0] = m_translation.x();
		rotation.GetColumn(3)[1] = m_translation.y();
		rotation.GetColumn(3)[2] = m_translation.z();

		TMatrix<T, 4, 4> scale = cd::Matrix4x4::Identity();
		scale.GetColumn(0)[0] *= m_scale.x();
		scale.GetColumn(1)[1] *= m_scale.y();
		scale.GetColumn(2)[2] *= m_scale.z();

		return rotation * scale;
	}

private:
	TVector<T, 3> m_translation;
	TQuaternion<T> m_rotation;
	TVector<T, 3> m_scale;
};

using Transform = TTransform<float>;

static_assert(10 * sizeof(float) == sizeof(Transform));
static_assert(std::is_standard_layout_v<Transform>&& std::is_trivial_v<Transform>);

}