#include "D3D12CommandBuffer.h"

#include <RHI/RHITypes.h>

namespace ow
{

void D3D12CommandBuffer::Begin()
{
}

void D3D12CommandBuffer::End()
{
}

void D3D12CommandBuffer::BeginRenderPass(IRHISwapChain* pSwapChain)
{
	//m_commandList->BeginRenderPass();
}

void D3D12CommandBuffer::EndRenderPass()
{
	m_commandList->EndRenderPass();
}

void D3D12CommandBuffer::SetViewport(float width, float height, float x, float y)
{
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = x;
	viewport.TopLeftY = y;
	viewport.Height = width;
	viewport.Width = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_commandList->RSSetViewports(1, &viewport);
}

void D3D12CommandBuffer::SetScissor(uint32 width, uint32 height, uint32 x, uint32 y)
{
	D3D12_RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	m_commandList->RSSetScissorRects(1, &rect);
}

void D3D12CommandBuffer::SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 firstBinding)
{
	D3D12_VERTEX_BUFFER_VIEW view;
	m_commandList->IASetVertexBuffers(0, 1, &view);
}

void D3D12CommandBuffer::SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16)
{
	D3D12_INDEX_BUFFER_VIEW view;
	m_commandList->IASetIndexBuffer(&view);
}

void D3D12CommandBuffer::Draw(uint32 vertexCount, uint32 vertexStart, uint32 instanceCount, uint32 instanceStart)
{
	m_commandList->DrawInstanced(vertexCount, instanceCount, vertexStart, instanceStart);
}

void D3D12CommandBuffer::DrawIndexed(uint32 indexCount, uint32 indexStart, uint32_t vertexOffset, uint32 instanceCount, uint32 instanceStart)
{
	m_commandList->DrawIndexedInstanced(indexCount, instanceCount, indexStart, vertexOffset, instanceStart);
}

}