#pragma once

#include "WindowsHeader.hpp"
#include "../IPlatformProcess.h"

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
	~WindowsProcess() = default;

	virtual bool Init() override;
};

}