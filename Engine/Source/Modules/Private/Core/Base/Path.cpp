#include <Core/String/Path.h>

#include <filesystem>

namespace ow
{

namespace
{

bool IsSlash(char c)
{
	return c == '\\' || c == '/';
}

String GetFileNameWithDotOffset(const String& path, size_t dotOffset = 0)
{
	String fileName = Path::GetFileName(path);
	auto dotPos = fileName.find('.');
	return std::string::npos != dotPos ? fileName.substr(0, dotPos + dotOffset) : fileName;
}

}

String Path::GetFileName(const String& path)
{
	auto itLastSlash = std::find_if(path.rbegin(), path.rend(),
		[](char c)
		{
			return IsSlash(c);
		});
	if (itLastSlash == path.rend())
	{
		return path;
	}

	return path.substr(itLastSlash.base() - path.begin());
}

String Path::GetFileNameWithoutExtension(const String& path)
{
	return GetFileNameWithDotOffset(path);
}

String Path::GetExtension(const String& path)
{
	// File extension is special in such case : "xxx.a.b" so rfind is not convenient to get ".a.b" directly.
	String fileName = GetFileName(path);
	auto dotPos = fileName.find('.');
	return std::string::npos != dotPos ? fileName.substr(dotPos + 1) : "";
}

String Path::ChangeExtension(const String& path, const String& extension)
{
	bool startWithDot = '.' == extension[0];
	return GetFileNameWithDotOffset(path, startWithDot ? 0 : 1) + extension;
}

bool Path::FileExists(const String& path)
{
	return std::filesystem::exists(path);
}

bool Path::IsFileReadonly(const String& path)
{
	auto permissions = std::filesystem::status(path).permissions();
	return (permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
}

String Path::GetDirectoryName(const String& path)
{
	return GetFileName(path);
}

String Path::GetDirectoryPath(const String& path)
{
	String fileName = GetFileName(path);
	return path.substr(0, path.length() - fileName.length());
}

bool Path::DirectoryExists(const String& path)
{
	return std::filesystem::is_directory(path);
}

String Path::GetWorkingDirectoryPath()
{
	return std::filesystem::current_path().generic_string();
}

String Path::GetTempPath()
{
	return std::filesystem::temp_directory_path().generic_string();
}

}