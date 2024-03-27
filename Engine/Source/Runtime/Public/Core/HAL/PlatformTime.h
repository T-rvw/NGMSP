#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

/// <summary>
/// Timer helps to calculate engine loop frame delta time or query current time stamp.
/// </summary>
class ENGINE_API PlatformTime
{
public:
	static void Init();
	static double Seconds();
	static double GetSecondsPerCycle();

public:
	PlatformTime() = delete;
	~PlatformTime() = delete;

private:
	static double SecondsPerCycle;
};

}