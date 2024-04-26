#pragma once

#include "D3D12Header.h"

#include <RHI/IRHICommandBuffer.h>

namespace ow
{

class D3D12CommandBuffer : public IRHICommandBuffer
{
public:
	D3D12CommandBuffer() = default;
	D3D12CommandBuffer(const D3D12CommandBuffer&) = delete;
	D3D12CommandBuffer& operator=(const D3D12CommandBuffer&) = delete;
	D3D12CommandBuffer(D3D12CommandBuffer&&) = default;
	D3D12CommandBuffer& operator=(D3D12CommandBuffer&&) = default;
	virtual ~D3D12CommandBuffer() = default;

	virtual void Begin() override;
	virtual void End() override;
	virtual void BeginRenderPass(IRHISwapChain* pSwapChain) override;
	virtual void EndRenderPass() override;
	virtual void SetViewport(float width, float height, float x = 0.0f, float y = 0.0f) override;
	virtual void SetScissor(uint32 width, uint32 height, uint32 x = 0, uint32 y = 0) override;
	virtual void SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 firstBinding = 0) override;
	virtual void SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16 = false) override;
	virtual void Draw(uint32 vertexCount, uint32 vertexStart = 0, uint32 instanceCount = 1, uint32 instanceStart = 0) override;
	virtual void DrawIndexed(uint32 indexCount, uint32 indexStart = 0, uint32_t vertexOffset = 0, uint32 instanceCount = 1, uint32 instanceStart = 0) override;

private:
	RefCountPtr<ID3D12GraphicsCommandList6> m_commandList;
};

}