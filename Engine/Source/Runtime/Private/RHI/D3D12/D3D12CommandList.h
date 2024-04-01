#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHICommandList.h>

namespace ow
{

class D3D12CommandList : public IRHICommandList
{
public:
	D3D12CommandList() = default;
	D3D12CommandList(const D3D12CommandList&) = delete;
	D3D12CommandList& operator=(const D3D12CommandList&) = delete;
	D3D12CommandList(D3D12CommandList&&) = default;
	D3D12CommandList& operator=(D3D12CommandList&&) = default;
	virtual ~D3D12CommandList() = default;

	void Init();
};

}