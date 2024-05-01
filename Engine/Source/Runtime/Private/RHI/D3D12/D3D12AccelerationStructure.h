#pragma once

#include "D3D12Header.h"

#include <RHI/IRHIAccelerationStructure.h>

namespace ow
{

class D3D12Device;

class D3D12AccelerationStructure : public IRHIAccelerationStructure
{
public:
	D3D12AccelerationStructure() = delete;
	explicit D3D12AccelerationStructure(const D3D12Device* pDevice, const RHIAccelerationStructureCreateInfo& createInfo);
	D3D12AccelerationStructure(const D3D12AccelerationStructure&) = delete;
	D3D12AccelerationStructure& operator=(const D3D12AccelerationStructure&) = delete;
	D3D12AccelerationStructure(D3D12AccelerationStructure&&) = default;
	D3D12AccelerationStructure& operator=(D3D12AccelerationStructure&&) = default;
	virtual ~D3D12AccelerationStructure() = default;
};

}