#pragma once

#include <Core/HAL/Platform.h>

#include "WindowsUndefines.h"

#include <windows.h>

namespace ow
{

static std::vector<WCHAR> CreateWideStringFromUTF8(const char* pValue)
{
	int32 count = MultiByteToWideChar(CP_UTF8, 0, pValue, -1, NULL, 0);
	std::vector<WCHAR> target(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, pValue, -1, target.data(), count);
	return target;
}

}