#include "WindowsHeader.hpp"
#include "WindowsTime.h"

namespace ow
{

static double SecondsPerCycle = 0.0;
void Time_Init()
{
	LARGE_INTEGER frequency;
	::QueryPerformanceFrequency(&frequency);

	SecondsPerCycle = 1.0 / (double)frequency.QuadPart;
}

double Time_Seconds()
{
	LARGE_INTEGER cycles;
	::QueryPerformanceCounter(&cycles);

	return (double)cycles.QuadPart * Time_GetSecondsPerCycle();
}

double Time_GetSecondsPerCycle()
{
	return SecondsPerCycle;
}

}