#pragma once

#include "D3D12Header.h"

#include <Core/HAL/BasicTypes.h>
#include <Core/HAL/PlatformEvent.h>
#include <RHI/IRHIFence.h>

#include <mutex>

namespace ow
{

struct RHIFenceCreateInfo;

class D3D12Device;

class D3D12Fence : public IRHIFence
{
public:
	D3D12Fence() = default;
	explicit D3D12Fence(const D3D12Device* pDevice, const RHIFenceCreateInfo& createInfo);
	D3D12Fence(const D3D12Fence&) = delete;
	D3D12Fence& operator=(const D3D12Fence&) = delete;
	D3D12Fence(D3D12Fence&&) = default;
	D3D12Fence& operator=(D3D12Fence&&) = default;
	virtual ~D3D12Fence();

	virtual uint64 Signal(uint64 fenceCount) override;
	virtual void Wait(uint64 fenceCount) override;
	virtual void Wait(uint64 fenceCount, uint64 timeout) override;
	virtual bool IsComplete(uint64 fenceCount) override;
	virtual void Reset(uint64 fenceCount) override;

private:
	RefCountPtr<ID3D12Fence> m_fence;
	std::mutex m_fenceWait;
	PlatformEvent m_completeEvent;
	uint64 m_currentValue;
	uint64 m_lastSignaled;
	uint64 m_lastCompleted;
};

}