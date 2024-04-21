#include "WindowsEvent.h"

#include <cassert>

namespace ow
{

WindowsEvent::~WindowsEvent()
{
	Shutdown();
}

void WindowsEvent::Init(const char* pName)
{
	m_name = pName;
	m_event = ::CreateEventExA(nullptr, m_name.c_str(), 0, EVENT_ALL_ACCESS);
}

void WindowsEvent::Shutdown()
{
	::CloseHandle(m_event);
}

void* WindowsEvent::GetHandle() const
{
	return m_event;
}

void WindowsEvent::Signal()
{
	::SetEvent(m_event);
}

void WindowsEvent::Wait()
{
	WaitForSingleObject(m_event, INFINITE);
}

}