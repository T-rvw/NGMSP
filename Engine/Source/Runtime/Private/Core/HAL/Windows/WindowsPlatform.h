#pragma once

#include <Core/HAL/BasicTypes.h>

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOATOM
#define NOKERNEL
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFIL
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOCRYPT
#define NOTAPE
#define NOIMAGE
#define NOPROXYSTUB
#define NORPC
#include <windows.h>

static WCHAR* CreateWideStringFromUTF8(const char* pValue)
{
	int32 count = MultiByteToWideChar(CP_UTF8, 0, pValue, -1, NULL, 0);
	WCHAR* pTarget = new WCHAR[count];
	if (!MultiByteToWideChar(CP_UTF8, 0, pValue, -1, pTarget, count))
	{
		delete[] pTarget;
		return NULL;
	}
	return pTarget;
}