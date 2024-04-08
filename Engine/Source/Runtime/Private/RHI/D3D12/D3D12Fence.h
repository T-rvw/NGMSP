#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIFence.h>

namespace ow
{

class D3D12Fence : public IRHIFence
{
public:
	D3D12Fence() = default;
	explicit D3D12Fence(ID3D12Fence* pFence);
	D3D12Fence(const D3D12Fence&) = delete;
	D3D12Fence& operator=(const D3D12Fence&) = delete;
	D3D12Fence(D3D12Fence&&) = default;
	D3D12Fence& operator=(D3D12Fence&&) = default;
	virtual ~D3D12Fence();

	void Init();

private:
	ComPtr<ID3D12Fence> m_fence;
};

}