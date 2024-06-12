#pragma once

#include <Core/Containers/Vector.h>

namespace ow
{

class FileLoader final
{
public:
	FileLoader() = delete;
	FileLoader(const FileLoader&) = delete;
	FileLoader& operator=(const FileLoader&) = delete;
	FileLoader(FileLoader&&) = delete;
	FileLoader& operator=(FileLoader&&) = delete;
	~FileLoader() = delete;

	static Vector<std::byte> LoadBinary(const char* pFilePath);
};

}