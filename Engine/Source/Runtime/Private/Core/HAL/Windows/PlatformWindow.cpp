#include <Core/HAL/PlatformWindow.h>
#include <Core/HAL/Template.h>

#include "PlatformWindowImpl.h"

namespace ow
{

PlatformWindow::PlatformWindow() = default;

PlatformWindow::PlatformWindow(const WindowCreateInfo& createInfo, void* pParentWindow)
{
	m_pImpl = new PlatformWindowImpl(createInfo, pParentWindow);
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

bool PlatformWindow::IsValid() const
{
	return m_pImpl->GetHandle() != nullptr;
}

void* PlatformWindow::GetHandle() const
{
	return m_pImpl->GetHandle();
}

}