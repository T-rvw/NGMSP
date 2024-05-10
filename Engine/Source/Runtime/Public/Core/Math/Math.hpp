#pragma once

#include <Core/Base/TypeTraits.h>
#include <Core/HAL/BasicTypes.h>
#include <Core/HAL/CompilerDefines.h>

#include <algorithm>
#include <cmath>
#include <climits>

namespace ow
{

class Math final
{
public:
	Math() = delete;

	static constexpr float FLOAT_EPSILON = 1.192092896e-07F;
	static constexpr float DOUBLE_EPSILON = 2.2204460492503131e-016;

	static constexpr float PI = 3.1415926535897932f;
	static constexpr float HALF_PI = PI / 2.0f;
	static constexpr float TWO_PI = PI * 2.0f;
	static constexpr float INVERSE_PI = 1.0f / PI;
	static constexpr float DEGREE_TO_RADIAN = PI / 180.0f;
	static constexpr float RADIAN_TO_DEGREE = 1 / DEGREE_TO_RADIAN;

	static constexpr float SQRT_2 = 1.4142135623730950488016887242097f;
	static constexpr float HALF_SQRT_2 = SQRT_2 / 2.0f;
	static constexpr float INVERSE_SQRT_2 = 1.0f / SQRT_2;

	static constexpr float SQRT_3 = 1.7320508075688772935274463415059f;
	static constexpr float HALF_SQRT_3 = SQRT_3 / 2.0f;
	static constexpr float INVERSE_SQRT_3 = 1.0f / SQRT_3;
	static constexpr float FLOAT_NAN = std::numeric_limits<float>::quiet_NaN();
	static constexpr float FLOAT_MIN = (std::numeric_limits<float>::min)();
	static constexpr float FLOAT_MAX = (std::numeric_limits<float>::max)();

	template<typename T>
	NODISCARD static constexpr T DegreeToRadian(T degree) { return degree * DEGREE_TO_RADIAN; }

	template<typename T>
	NODISCARD static constexpr T RadianToDegree(T radian) { return radian * RADIAN_TO_DEGREE; }

	template<typename T>
	static constexpr T GetEpsilon()
	{
		if constexpr (std::is_same<float, T>())
		{
			return FLOAT_EPSILON;
		}
		else if constexpr (std::is_same<double, T>())
		{
			return DOUBLE_EPSILON;
		}
		else
		{
			return static_cast<T>(0);
		}
	}

	template<typename T>
	NODISCARD static constexpr bool Equals(T a, T b, T eps)
	{
		return std::abs(a - b) <= eps;
	}

	template<typename T>
	NODISCARD static constexpr bool Equals(T a, T b)
	{
		return Equals(a, b, GetEpsilon<T>());
	}

	template<typename T>
	NODISCARD static constexpr bool IsSmallerThan(T a, T b)
	{
		return a + GetEpsilon<T>() < b;
	}

	template<typename T>
	NODISCARD static constexpr bool IsNotLargerThan(T a, T b)
	{
		return a + GetEpsilon<T>() <= b;
	}

	template<typename T>
	NODISCARD static constexpr bool IsLargerThan(T a, T b)
	{
		return a > b + GetEpsilon<T>();
	}

	template<typename T>
	NODISCARD static constexpr bool IsNotSmallerThan(T a, T b)
	{
		return a >= b + GetEpsilon<T>();
	}

	// Convert oldValue in [oldMin, oldMax] to newValue in [newMin, newMax].
	template<typename T>
	NODISCARD static constexpr T GetValueInNewRange(T oldValue, T oldMin, T oldMax, T newMin, T newMax)
	{
		return newMin + (oldValue - oldMin) * (newMax - newMin) / (oldMax - oldMin);
	}

	NODISCARD static uint32 CastFloatToU32(float value)
	{
		struct FloatU32Mem
		{
			union
			{
				float f;
				uint32 u;
			};
		};

		FloatU32Mem m;
		m.f = value;
		return m.u;
	}
};

}