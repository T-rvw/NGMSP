#pragma once

#include "WindowsHeader.h"

#include <Core/HAL/Interfaces/IPlatformProcess.h>

namespace ow
{

class WindowsProcess : public IPlatformProcess
{
public:
	WindowsProcess() = default;
	WindowsProcess(const WindowsProcess&) = delete;
	WindowsProcess& operator=(const WindowsProcess&) = delete;
	WindowsProcess(WindowsProcess&&) = default;
	WindowsProcess& operator=(WindowsProcess&&) = default;
	virtual ~WindowsProcess() = default;

	virtual bool Init() override;
};

}