#pragma once

#include "D3D12Header.h"

#include <Core/HAL/BasicTypes.h>
#include <RHI/Interfaces/IRHIFence.h>

namespace ow
{

class D3D12Fence : public IRHIFence
{
public:
	D3D12Fence() = default;
	explicit D3D12Fence(ID3D12Device* pDevice, ID3D12Fence* pFence);
	D3D12Fence(const D3D12Fence&) = delete;
	D3D12Fence& operator=(const D3D12Fence&) = delete;
	D3D12Fence(D3D12Fence&&) = default;
	D3D12Fence& operator=(D3D12Fence&&) = default;
	virtual ~D3D12Fence();

	virtual void Wait(uint64 timeout) override;
	virtual void Reset() override;

private:
	ComPtr<ID3D12Device> m_device;
	ComPtr<ID3D12Fence> m_fence;
	uint64 m_fenceValue = 0;
};

}