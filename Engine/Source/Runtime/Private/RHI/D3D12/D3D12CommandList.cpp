#include "D3D12CommandList.h"

#include "D3D12Buffer.h"
#include "D3D12CommandPool.h"
#include "D3D12Device.h"
#include "D3D12SwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12CommandList::D3D12CommandList(const D3D12CommandPool* pCommandPool, const RHICommandListCreateInfo& createInfo) :
	m_pCommandPool(pCommandPool)
{
	auto d3d12Device = pCommandPool->GetDevice()->GetHandle();
	d3d12Device->CreateCommandList(0, m_pCommandPool->GetType(), m_pCommandPool->GetHandle(), nullptr, IID_PPV_ARGS(&m_commandList));
}

void D3D12CommandList::Begin()
{
	m_commandList->Reset(m_pCommandPool->GetHandle(), nullptr);
}

void D3D12CommandList::End()
{
	m_commandList->Close();
}

void D3D12CommandList::BeginRenderPass(IRHISwapChain* pSwapChain)
{
	auto* pD3D12SwapChain = static_cast<D3D12SwapChain*>(pSwapChain);
	//m_commandList->BeginRenderPass(pD3D12SwapChain->GetBackBufferCount(), );
}

void D3D12CommandList::EndRenderPass()
{
	m_commandList->EndRenderPass();
}

void D3D12CommandList::SetViewport(float width, float height, float x, float y)
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

void D3D12CommandList::SetScissor(uint32 width, uint32 height, uint32 x, uint32 y)
{
	D3D12_RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	m_commandList->RSSetScissorRects(1, &rect);
}

void D3D12CommandList::SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingStart)
{
	D3D12Buffer* pD3D12Buffer = static_cast<D3D12Buffer*>(pVertexBuffer);

	const auto& bufferCreateInfo = pD3D12Buffer->GetCreateInfo();
	D3D12_VERTEX_BUFFER_VIEW bufferView;
	bufferView.BufferLocation;
	bufferView.SizeInBytes = bufferCreateInfo.SizeInBytes;
	bufferView.StrideInBytes = bufferCreateInfo.Stride;
	m_commandList->IASetVertexBuffers(bindingStart, 1, &bufferView);
}

void D3D12CommandList::SetVertexBuffers(const Vector<IRHIBuffer*>& vertexBuffers, uint32 bindingStart)
{
	constexpr uint64 MaxVertexBufferCount = 4;
	Assert(vertexBuffers.size() <= MaxVertexBufferCount);

	uint32 bufferCount = 0;
	D3D12_VERTEX_BUFFER_VIEW bufferViews[MaxVertexBufferCount];
	for (auto* pVertexBuffer : vertexBuffers)
	{
		auto& bufferView = bufferViews[bufferCount];
		bufferView.BufferLocation = 0;
		bufferView.StrideInBytes = 0;
		bufferView.SizeInBytes = 0;
		++bufferCount;
	}
	m_commandList->IASetVertexBuffers(bindingStart, bufferCount, bufferViews);
}

void D3D12CommandList::SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16)
{
	D3D12_INDEX_BUFFER_VIEW view;
	view.BufferLocation = 0;
	view.Format = useUInt16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	view.SizeInBytes = 0;
	m_commandList->IASetIndexBuffer(&view);
}

void D3D12CommandList::Draw(uint32 vertexCount, uint32 vertexStart)
{
	m_commandList->DrawInstanced(vertexCount, 1, vertexStart, 0);
}

void D3D12CommandList::DrawInstanced(uint32 vertexCount, uint32 vertexStart, uint32 instanceCount, uint32 instanceStart)
{
	m_commandList->DrawInstanced(vertexCount, instanceCount, vertexStart, instanceStart);
}

void D3D12CommandList::DrawIndexed(uint32 indexCount, uint32 indexStart, uint32_t vertexOffset)
{
	m_commandList->DrawIndexedInstanced(indexCount, 1, indexStart, vertexOffset, 0);
}

void D3D12CommandList::DrawIndexedInstanced(uint32 indexCount, uint32 instanceCount, uint32 indexStart, uint32 instanceStart, uint32_t vertexOffset)
{
	m_commandList->DrawIndexedInstanced(indexCount, instanceCount, indexStart, vertexOffset, instanceStart);
}

}