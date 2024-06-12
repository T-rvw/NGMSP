#pragma once

#include <Core/HAL/APIDefines.h>
#include <Core/Containers/Vector.h>

namespace ow
{

class CORE_API FileLoader final
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