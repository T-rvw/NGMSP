#pragma once

#include "D3D12Header.h"

#include <RHI/IRHICommandPool.h>

namespace ow
{

struct RHICommandPoolCreateInfo;

class D3D12Device;

class D3D12CommandPool : public IRHICommandPool
{
public:
	D3D12CommandPool() = delete;
	explicit D3D12CommandPool(const D3D12Device* pDevice, const RHICommandPoolCreateInfo& createInfo);
	D3D12CommandPool(const D3D12CommandPool&) = delete;
	D3D12CommandPool& operator=(const D3D12CommandPool&) = delete;
	D3D12CommandPool(D3D12CommandPool&&) = default;
	D3D12CommandPool& operator=(D3D12CommandPool&&) = default;
	virtual ~D3D12CommandPool() = default;

	virtual CommandListHandle CreateCommandList(const RHICommandListCreateInfo& createInfo) override;

	const D3D12Device* GetDevice() const { return m_pDevice; }
	D3D12_COMMAND_LIST_TYPE GetType() const { return m_commandType; }
	RefCountPtr<ID3D12CommandAllocator> GetHandle() const { return m_commandPool; }
	
private:
	const D3D12Device* m_pDevice;
	D3D12_COMMAND_LIST_TYPE m_commandType;
	RefCountPtr<ID3D12CommandAllocator> m_commandPool;
};

}