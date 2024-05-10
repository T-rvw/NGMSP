#pragma once

#include <Core/HAL/APIDefines.h>

namespace ow
{

/// <summary>
/// Timer helps to calculate engine loop frame delta time or query current time stamp.
/// </summary>
class CORE_API PlatformTime final
{
public:
	PlatformTime() = delete;

	static void Init();
	static double Seconds();
	static double GetSecondsPerCycle();

private:
	static double SecondsPerCycle;
};

}