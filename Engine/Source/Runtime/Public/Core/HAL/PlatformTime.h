#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

/// <summary>
/// Window means a GUI proxy which combines user inputs and graphics backend or other modules.
/// Output rendering image to window client or do something based on user inputs.
/// </summary>
class ENGINE_API PlatformTime
{
public:
	static double Init();
	static double Seconds();
	static double GetSecondsPerCycle();

public:
	PlatformTime() = delete;
	~PlatformTime() = delete;

private:
	static double SecondsPerCycle;
};

}