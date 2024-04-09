#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHISurface.h>

namespace ow
{

class D3D12Surface : public IRHISurface
{
public:
	D3D12Surface() = default;
	D3D12Surface(const D3D12Surface&) = delete;
	D3D12Surface& operator=(const D3D12Surface&) = delete;
	D3D12Surface(D3D12Surface&&) = default;
	D3D12Surface& operator=(D3D12Surface&&) = default;
	virtual ~D3D12Surface() = default;

	virtual void* GetHandle() const override;
};

}