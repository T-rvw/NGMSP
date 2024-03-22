#pragma once

namespace ow
{

class PlatformModuleImpl;

class PlatformModule
{
public:
	PlatformModule();
	explicit PlatformModule(const char* pModuleFilePath);
	PlatformModule(const PlatformModule&) = delete;
	PlatformModule& operator=(const PlatformModule&) = delete;
	PlatformModule(PlatformModule&& other);
	PlatformModule& operator=(PlatformModule&& other);
	~PlatformModule();

	bool IsValid() const;
	void* GetHandle() const;

	bool Load();
	void Unload();

private:
	PlatformModuleImpl* m_pImpl = nullptr;
};

}