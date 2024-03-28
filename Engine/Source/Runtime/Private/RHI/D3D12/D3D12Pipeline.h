#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIPipeline.h>

namespace ow
{

class D3D12Pipeline : public IRHIPipeline
{
public:
	D3D12Pipeline() = default;
	D3D12Pipeline(const D3D12Pipeline&) = delete;
	D3D12Pipeline& operator=(const D3D12Pipeline&) = delete;
	D3D12Pipeline(D3D12Pipeline&&) = default;
	D3D12Pipeline& operator=(D3D12Pipeline&&) = default;
	virtual ~D3D12Pipeline() = default;

	void Init();
};

}