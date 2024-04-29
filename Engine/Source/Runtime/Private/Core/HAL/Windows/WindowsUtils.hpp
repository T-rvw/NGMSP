#pragma once

#include "WindowsUndefines.h"

#include <Core/Base/Vector.h>
#include <Core/HAL/BasicTypes.h>

#include <windows.h>

namespace ow
{

static Vector<WCHAR> CreateWideStringFromUTF8(const char* pValue)
{
	int32 count = MultiByteToWideChar(CP_UTF8, 0, pValue, -1, NULL, 0);
	Vector<WCHAR> target(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, pValue, -1, target.data(), count);
	return target;
}

static Vector<char> CreateUTF8StringFromWide(const wchar_t* pValue)
{
	int32_t count = WideCharToMultiByte(CP_UTF8, 0, pValue, -1, NULL, 0, NULL, NULL);
	Vector<char> target(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, pValue, -1, target.data(), count, NULL, NULL);
	return target;
}

}