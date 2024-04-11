#pragma once

namespace ow
{

class IPlatformModule
{
public:
	virtual bool Load() = 0;
	virtual void Unload() = 0;

	virtual const char* GetModuleName() const = 0;
	virtual void SetModuleName(const char* pModuleName) = 0;

	virtual const char* GetModulePath() const = 0;
	virtual void SetModulePath(const char* pModulePath) = 0;

	virtual void* GetHandle() const = 0;
	virtual void* GetFunctionAddress(const char* pFuncName) = 0;
};

}