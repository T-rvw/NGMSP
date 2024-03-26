#include <Core/HAL/PlatformTime.h>

#include <Core/HAL/Platform/Windows/WindowsPlatform.h>

namespace ow
{

double PlatformTime::SecondsPerCycle = 0.0;

double PlatformTime::Init()
{
	LARGE_INTEGER frequency;
	::QueryPerformanceFrequency(&frequency);

	SecondsPerCycle = 1.0 / (double)frequency.QuadPart;

	return PlatformTime::Seconds();
}

double PlatformTime::Seconds()
{
	LARGE_INTEGER cycles;
	::QueryPerformanceCounter(&cycles);

	return (double)cycles.QuadPart * GetSecondsPerCycle();
}

double PlatformTime::GetSecondsPerCycle()
{
	return SecondsPerCycle;
}

}