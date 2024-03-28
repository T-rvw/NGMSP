#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHICommandPool.h>

namespace ow
{

class D3D12CommandPool : public IRHICommandPool
{
public:
	D3D12CommandPool() = default;
	D3D12CommandPool(const D3D12CommandPool&) = delete;
	D3D12CommandPool& operator=(const D3D12CommandPool&) = delete;
	D3D12CommandPool(D3D12CommandPool&&) = default;
	D3D12CommandPool& operator=(D3D12CommandPool&&) = default;
	virtual ~D3D12CommandPool() = default;

	void Init();
};

}