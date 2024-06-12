#include <Core/Misc/FileLoader.h>

#include <fstream>

namespace ow
{

Vector<std::byte> FileLoader::LoadBinary(const char* pFilePath)
{
	Vector<std::byte> fileData;

	std::ifstream fin(pFilePath, std::ios::in | std::ios::binary);
	if (!fin.is_open())
	{
		return fileData;
	}

	fin.seekg(0L, std::ios::end);
	size_t fileSize = fin.tellg();
	fin.seekg(0L, std::ios::beg);
	fileData.resize(fileSize);
	fin.read(reinterpret_cast<char*>(fileData.data()), fileSize);
	fin.close();

	return fileData;
}

}