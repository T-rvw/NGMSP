#pragma once

#include <Core/HAL/APIDefinition.h>
#include <Core/HAL/BasicTypes.h>

namespace ow
{

class CORE_API CString
{
public:
	static constexpr char ToLower(char c)
	{
		constexpr char offset = 'Z' - 'z';
		return c >= 'A' && c <= 'Z' ? c - offset : c;
	}

	static constexpr char ToUpper(char c)
	{
		constexpr char offset = 'Z' - 'z';
		return c >= 'a' && c <= 'z' ? c + offset : c;
	}

	static uint32 Length(const char* str);
	static bool Compare(const char* str1, const char* str2, bool caseSensitive = true);
};

}