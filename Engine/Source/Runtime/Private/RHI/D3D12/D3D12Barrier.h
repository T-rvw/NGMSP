#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIBarrier.h>

namespace ow
{

class D3D12Barrier : public IRHIBarrier
{
public:
	D3D12Barrier() = default;
	//explicit D3D12Barrier();
	D3D12Barrier(const D3D12Barrier&) = delete;
	D3D12Barrier& operator=(const D3D12Barrier&) = delete;
	D3D12Barrier(D3D12Barrier&&) = default;
	D3D12Barrier& operator=(D3D12Barrier&&) = default;
	virtual ~D3D12Barrier();

	void Init();
};

}