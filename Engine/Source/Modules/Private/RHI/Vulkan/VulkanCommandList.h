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

	virtual void Begin() override;
	virtual void End() override;

	virtual void BeginRenderPass(IRHISwapChain* pSwapChain) override;
	virtual void EndRenderPass() override;

	virtual void SetViewport(float width, float height, float x = 0.0f, float y = 0.0f) override;
	virtual void SetScissor(uint32 width, uint32 height, uint32 x = 0, uint32 y = 0) override;

	virtual void SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingStart = 0) override;
	virtual void SetVertexBuffers(const Vector<IRHIBuffer*>& vertexBuffers, uint32 bindingStart = 0) override;
	virtual void SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16 = false) override;

	virtual void Draw(uint32 vertexCount, uint32 vertexStart = 0) override;
	virtual void DrawInstanced(uint32 vertexCount, uint32 instanceCount, uint32 vertexStart = 0, uint32 instanceStart = 0) override;
	virtual void DrawIndexed(uint32 indexCount, uint32 indexStart = 0, uint32_t vertexOffset = 0) override;
	virtual void DrawIndexedInstanced(uint32 indexCount, uint32 instanceCount = 1, uint32 indexStart = 0, uint32 instanceStart = 0, uint32_t vertexOffset = 0) override;

	VkCommandBuffer GetHandle() const { return m_commandBuffer; }
	const VkCommandBuffer* GetAddressOf() const { return &m_commandBuffer; }

private:
	VkCommandBuffer m_commandBuffer;
};

}