#include "D3D12Fence.h"

#include "D3D12Device.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Fence::D3D12Fence(const D3D12Device* pDevice, const RHIFenceCreateInfo& createInfo) :
	m_currentValue(createInfo.InitialValue + 1),
	m_lastSignaled(0),
	m_lastCompleted(createInfo.InitialValue)
{
	D3D12_VERIFY(pDevice->GetHandle()->CreateFence(m_lastCompleted, D3D12Types::ToD3D12(createInfo.FenceType), IID_PPV_ARGS(&m_fence)));
	m_completeEvent.Init("FenceEvent");
}

D3D12Fence::~D3D12Fence()
{
}

uint64 D3D12Fence::Signal(uint64 fenceValue)
{
	m_lastSignaled = fenceValue;
	m_lastCompleted = fenceValue;
	m_currentValue++;
	return m_lastSignaled;
}

void D3D12Fence::Wait(uint64 fenceValue)
{
	if (IsComplete(fenceValue))
	{
		return;
	}

	std::lock_guard<std::mutex> lockGuard(m_fenceWait);
	HANDLE completeEventHandle = m_completeEvent.GetHandle();
	m_fence->SetEventOnCompletion(fenceValue, completeEventHandle);
	WaitForSingleObject(completeEventHandle, INFINITE);
	m_lastCompleted = m_fence->GetCompletedValue();
}

void D3D12Fence::Wait()
{
	Wait(m_lastSignaled);
}

bool D3D12Fence::IsComplete(uint64 fenceValue)
{
	if (fenceValue <= m_lastCompleted)
	{
		return true;
	}

	auto completedValue = m_fence->GetCompletedValue();
	m_lastCompleted = m_lastCompleted > completedValue ? m_lastCompleted : completedValue;
	return fenceValue <= m_lastCompleted;
}

void D3D12Fence::Reset()
{

}

}