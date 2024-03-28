#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIBuffer.h>

namespace ow
{

class D3D12Buffer : public IRHIBuffer
{
public:
	D3D12Buffer() = default;
	D3D12Buffer(const D3D12Buffer&) = delete;
	D3D12Buffer& operator=(const D3D12Buffer&) = delete;
	D3D12Buffer(D3D12Buffer&&) = default;
	D3D12Buffer& operator=(D3D12Buffer&&) = default;
	virtual ~D3D12Buffer() = default;

	void Init();
};

}