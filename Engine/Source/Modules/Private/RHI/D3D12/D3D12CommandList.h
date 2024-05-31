#pragma once

#include "D3D12Header.h"

#include <RHI/IRHICommandList.h>

namespace ow
{

struct RHICommandListCreateInfo;

class D3D12CommandPool;

class D3D12CommandList : public IRHICommandList
{
public:
	D3D12CommandList() = default;
	explicit D3D12CommandList(const D3D12CommandPool* pCommandPool, const RHICommandListCreateInfo& createInfo);
	D3D12CommandList(const D3D12CommandList&) = delete;
	D3D12CommandList& operator=(const D3D12CommandList&) = delete;
	D3D12CommandList(D3D12CommandList&&) = default;
	D3D12CommandList& operator=(D3D12CommandList&&) = default;
	virtual ~D3D12CommandList() = default;

	// Binding
	virtual void Begin() override;
	virtual void End() override;

	virtual void BeginRenderPass(IRHISwapChain* pSwapChain) override;
	virtual void EndRenderPass() override;

	// Resource
	virtual void SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingSlot = 0) override;
	virtual void SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16 = false) override;

	// View
	virtual void SetViewport(const Viewport& viewport) override;
	virtual void SetScissor(const Rect& rect) override;

	// Dispatch
	virtual void Dispath(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ) override;

	// Draw
	virtual void Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) override;
	virtual void DrawIndirect(IRHIBuffer* pArgBuffer, uint32 offset, uint32 drawCount, uint32 stride) override;
	virtual void DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, uint32 vertexOffset, uint32 firstInstance) override;

private:
	const D3D12CommandPool* m_pCommandPool;
	RefCountPtr<ID3D12GraphicsCommandList6> m_commandList;
};

}