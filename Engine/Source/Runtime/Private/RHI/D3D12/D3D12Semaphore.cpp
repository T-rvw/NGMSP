#include "D3D12Semaphore.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Semaphore::D3D12Semaphore(const RHISemaphoreCreateInfo& createInfo)
{
	m_semaphore.Init();
}

D3D12Semaphore::~D3D12Semaphore()
{
}

}