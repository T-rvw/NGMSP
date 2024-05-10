#include <Core/Base/CString.h>

namespace ow
{

uint32 CString::Length(const char* str)
{
	uint32 length = 0;
	while (*str++ != '\0')
	{
		++length;
	}

	return length;
}

bool CString::Compare(const char* str1, const char* str2, bool caseSensitive)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (caseSensitive)
		{
			if (*str1 != *str2)
			{
				return false;
			}
		}
		else
		{
			if (ToLower(*str1) != ToLower(*str2))
			{
				return false;
			}
		}
		++str1;
		++str2;
	}

	return *str1 == *str2;
}

}