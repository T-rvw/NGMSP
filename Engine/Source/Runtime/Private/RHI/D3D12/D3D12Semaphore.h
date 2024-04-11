#pragma once

#include "D3D12Header.h"

#include <Core/HAL/PlatformSemaphore.h>
#include <RHI/IRHISemaphore.h>

namespace ow
{

class D3D12Semaphore : public IRHISemaphore
{
public:
	D3D12Semaphore() = default;
	D3D12Semaphore(const D3D12Semaphore&) = delete;
	D3D12Semaphore& operator=(const D3D12Semaphore&) = delete;
	D3D12Semaphore(D3D12Semaphore&&) = default;
	D3D12Semaphore& operator=(D3D12Semaphore&&) = default;
	virtual ~D3D12Semaphore();

	void Init();

private:
	PlatformSemaphore m_semaphore;
};

}