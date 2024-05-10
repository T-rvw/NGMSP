#pragma once

#include <Core/HAL/APIDefinition.h>
#include <Core/Base/String.h>

namespace ow
{

class CORE_API Path
{
public:
	static String GetFileName(const String& path);
	static String GetFileNameWithoutExtension(const String& path);
	static String GetExtension(const String& path);
	static String ChangeExtension(const String& path, const String& extension);
	static bool FileExists(const String& path);
	static bool IsFileReadonly(const String& path);

	static String GetDirectoryName(const String& path);
	static String GetDirectoryPath(const String& path);
	static bool DirectoryExists(const String& path);

	static String GetWorkingDirectoryPath();
	static String GetTempPath();
};

}