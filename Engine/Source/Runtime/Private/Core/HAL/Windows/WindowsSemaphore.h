#pragma once

#include "WindowsHeader.h"

#include <Core/HAL/Interfaces/IPlatformSemaphore.h>

namespace ow
{

class WindowsSemaphore : public IPlatformSemaphore
{
public:
	WindowsSemaphore() = default;
	WindowsSemaphore(const WindowsSemaphore&) = delete;
	WindowsSemaphore& operator=(const WindowsSemaphore&) = delete;
	WindowsSemaphore(WindowsSemaphore&&) = default;
	WindowsSemaphore& operator=(WindowsSemaphore&&) = default;
	~WindowsSemaphore();

	virtual void Init(int32 initialCount, int32 maxCount) override;
	virtual void Wait() const override;
	virtual void Signal(int32 releaseCount) const override;

private:
	HANDLE m_semaphore = NULL;
};

}