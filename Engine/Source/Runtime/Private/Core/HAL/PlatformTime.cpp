#include <Core/HAL/PlatformTime.h>

#include "PlatformImplTypes.h"

namespace ow
{

void PlatformTime::Init()
{
	return Time_Init();
}

double PlatformTime::Seconds()
{
	return Time_Seconds();
}

double PlatformTime::GetSecondsPerCycle()
{
	return Time_GetSecondsPerCycle();
}

}