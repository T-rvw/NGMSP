#pragma once

namespace ow
{

class IPlatformModule
{
public:
	virtual bool Init(const char* pFilePath) = 0;
	virtual void Free() = 0;

	virtual void* GetHandle() const = 0;
	virtual void* GetFunctionAddress(const char* pFuncName) = 0;
};

}