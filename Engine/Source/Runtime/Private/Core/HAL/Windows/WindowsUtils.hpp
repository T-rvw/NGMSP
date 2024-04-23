#pragma once

#include "WindowsUndefines.h"

#include <Core/HAL/BasicTypes.h>

#include <windows.h>

#include <vector>

namespace ow
{

static std::vector<WCHAR> CreateWideStringFromUTF8(const char* pValue)
{
	int32 count = MultiByteToWideChar(CP_UTF8, 0, pValue, -1, NULL, 0);
	std::vector<WCHAR> target(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, pValue, -1, target.data(), count);
	return target;
}

static std::vector<char> CreateUTF8StringFromWide(const wchar_t* pValue)
{
	int32_t count = WideCharToMultiByte(CP_UTF8, 0, pValue, -1, NULL, 0, NULL, NULL);
	std::vector<char> target(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, pValue, -1, target.data(), count, NULL, NULL);
	return target;
}

}