#include <Core/HAL/PlatformModule.h>

#include "PlatformModuleImpl.h"

namespace ow
{

PlatformModule::PlatformModule() = default;

PlatformModule::PlatformModule(PlatformModule&& other)
{
	*this = MoveTemp(other);
}

PlatformModule& PlatformModule::operator=(PlatformModule&& other)
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformModule::~PlatformModule()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

bool PlatformModule::IsValid() const
{
	return m_pImpl->GetHandle() != nullptr;
}

void* PlatformModule::GetHandle() const
{
	return m_pImpl->GetHandle();
}

bool PlatformModule::Load(const char* pFilePath)
{
	return m_pImpl->Load(pFilePath);
}

void PlatformModule::Unload()
{
	m_pImpl->Unload();
}

}