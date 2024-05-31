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

void D3D12CommandList::SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingSlot)
{
	D3D12Buffer* pD3D12Buffer = static_cast<D3D12Buffer*>(pVertexBuffer);

	const auto& bufferCreateInfo = pD3D12Buffer->GetCreateInfo();
	D3D12_VERTEX_BUFFER_VIEW bufferView;
	bufferView.BufferLocation;
	bufferView.SizeInBytes = bufferCreateInfo.SizeInBytes;
	bufferView.StrideInBytes = bufferCreateInfo.Stride;
	m_commandList->IASetVertexBuffers(bindingSlot, 1, &bufferView);
}

void D3D12CommandList::SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16)
{
	D3D12_INDEX_BUFFER_VIEW view;
	view.BufferLocation = 0;
	view.Format = useUInt16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	view.SizeInBytes = 0;
	m_commandList->IASetIndexBuffer(&view);
}

void D3D12CommandList::SetViewport(const Viewport& viewport)
{
	auto d3d12Viewport = D3D12Types::ToD3D12(viewport);
	m_commandList->RSSetViewports(1, &d3d12Viewport);
}

void D3D12CommandList::SetScissor(const Rect& rect)
{
	auto d3d12Rect = D3D12Types::ToD3D12(rect);
	m_commandList->RSSetScissorRects(1, &d3d12Rect);
}

void D3D12CommandList::Dispath(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ)
{
	m_commandList->Dispatch(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
}

void D3D12CommandList::Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance)
{
	m_commandList->DrawInstanced(vertexCount, instanceCount, firstVertex, firstInstance);
}

void D3D12CommandList::DrawIndirect(IRHIBuffer* pArgBuffer, uint32 offset, uint32 drawCount, uint32 stride)
{
	// CommandSignature storage in device.
	//m_commandList->ExecuteIndirect;
}

void D3D12CommandList::DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, uint32 vertexOffset, uint32 firstInstance)
{
	m_commandList->DrawIndexedInstanced(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

}