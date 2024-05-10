#pragma once

#include "WindowsHeader.h"

#include <Core/HAL/Interfaces/IPlatformEvent.h>
#include <Core/String/String.h>

namespace ow
{

class WindowsEvent : public IPlatformEvent
{
public:
	WindowsEvent() = default;
	WindowsEvent(const WindowsEvent&) = delete;
	WindowsEvent& operator=(const WindowsEvent&) = delete;
	WindowsEvent(WindowsEvent&&) = default;
	WindowsEvent& operator=(WindowsEvent&&) = default;
	virtual ~WindowsEvent();

	virtual void Init(const char* pName) override;
	virtual void Shutdown() override;
	virtual void* GetHandle() const override;
	virtual void Signal() override;
	virtual void Wait() override;

private:
	String m_name;
	HANDLE m_event;
};

}