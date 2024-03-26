#include <Core/HAL/PlatformWindow.h>

#include "PlatformWindowImpl.h"

namespace ow
{

PlatformWindow::PlatformWindow()
{
	m_pImpl = new PlatformWindowImpl();
}

PlatformWindow::PlatformWindow(PlatformWindow&& other) noexcept
{
	*this = MoveTemp(other);
}

PlatformWindow& PlatformWindow::operator=(PlatformWindow&& other) noexcept
{
	std::swap(m_pImpl, other.m_pImpl);
	return *this;
}

PlatformWindow::~PlatformWindow()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void PlatformWindow::Init(const WindowCreateInfo& createInfo, void* pInstance)
{
	m_pImpl->Init(createInfo, pInstance);
}

bool PlatformWindow::IsValid() const
{
	return m_pImpl->GetHandle() != nullptr;
}

void* PlatformWindow::GetHandle() const
{
	return m_pImpl->GetHandle();
}

}