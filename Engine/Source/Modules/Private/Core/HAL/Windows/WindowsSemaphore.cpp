#include "WindowsSemaphore.h"

namespace ow
{

WindowsSemaphore::~WindowsSemaphore()
{
	CloseHandle(m_semaphore);
}

void WindowsSemaphore::Init(int32 initialCount, int32 maxCount)
{
	m_semaphore = ::CreateSemaphore(NULL, initialCount, maxCount, NULL);
}

void WindowsSemaphore::Wait() const
{
	::WaitForSingleObject(m_semaphore, INFINITE);
}

void WindowsSemaphore::Signal(int32 releaseCount) const
{
	::ReleaseSemaphore(m_semaphore, releaseCount, NULL);
}

}