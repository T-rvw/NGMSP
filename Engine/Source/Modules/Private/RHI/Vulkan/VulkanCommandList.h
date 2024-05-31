#pragma once

#include "VulkanHeader.h"

#include <RHI//IRHICommandList.h>

namespace ow
{

class VulkanCommandPool;

class VulkanCommandList : public IRHICommandList
{
public:
	VulkanCommandList() = delete;
	explicit VulkanCommandList(const VulkanCommandPool* pCommandPool, const RHICommandListCreateInfo& createInfo);
	VulkanCommandList(const VulkanCommandList&) = delete;
	VulkanCommandList& operator=(const VulkanCommandList&) = delete;
	VulkanCommandList(VulkanCommandList&&) = default;
	VulkanCommandList& operator=(VulkanCommandList&&) = default;
	virtual ~VulkanCommandList();

	// Binding
	virtual void Begin() override;
	virtual void End() override;

	virtual void BeginRenderPass(IRHISwapChain* pSwapChain) override;
	virtual void EndRenderPass() override;

	// Resource
	virtual void SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingSlot = 0) override;
	virtual void SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16 = false) override;

	// View
	virtual void SetViewport(const Viewport& rect) override;
	virtual void SetScissor(const Rect& rect) override;

	// Dispatch
	virtual void Dispath(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ) override;

	// Draw
	virtual void Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) override;
	virtual void DrawIndirect(IRHIBuffer* pArgBuffer, uint32 offset, uint32 drawCount, uint32 stride) override;
	virtual void DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, uint32 vertexOffset, uint32 firstInstance) override;

	VkCommandBuffer GetHandle() const { return m_commandBuffer; }
	const VkCommandBuffer* GetAddressOf() const { return &m_commandBuffer; }

private:
	VkCommandBuffer m_commandBuffer;
};

}