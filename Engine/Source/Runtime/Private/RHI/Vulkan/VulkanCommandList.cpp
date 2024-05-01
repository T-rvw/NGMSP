#include "VulkanCommandList.h"

#include "VulkanBuffer.h"
#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandList::VulkanCommandList(const VulkanCommandPool* pCommandPool, const RHICommandListCreateInfo& createInfo)
{
	VkCommandBufferAllocateInfo commandBufferInfo = {};
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferInfo.commandPool = pCommandPool->GetHandle();
	commandBufferInfo.commandBufferCount = 1;
	VK_VERIFY(vkAllocateCommandBuffers(pCommandPool->GetDevice()->GetHandle(), &commandBufferInfo, &m_commandBuffer));
}

VulkanCommandList::~VulkanCommandList()
{
}

void VulkanCommandList::Begin()
{
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	VK_VERIFY(vkBeginCommandBuffer(m_commandBuffer, &beginInfo));
}

void VulkanCommandList::End()
{
	VK_VERIFY(vkEndCommandBuffer(m_commandBuffer));
}

void VulkanCommandList::BeginRenderPass(IRHISwapChain* pSwapChain)
{
	auto* pVulkanSwapChain = static_cast<VulkanSwapChain*>(pSwapChain);
	uint32 backBufferIndex = pVulkanSwapChain->GetCurrentBackBufferIndex();

	VkClearValue clearValue = {};
	clearValue.color.float32[0] = 0.0f;
	clearValue.color.float32[1] = 0.0f;
	clearValue.color.float32[2] = 0.0f;
	clearValue.color.float32[3] = 1.0f;

	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = pVulkanSwapChain->GetFrameBuffer(backBufferIndex);
	renderPassBeginInfo.renderArea.extent = pVulkanSwapChain->GetSwapChainExtent();
	renderPassBeginInfo.renderPass = pVulkanSwapChain->GetRenderPass();
	renderPassBeginInfo.pClearValues = &clearValue;
	renderPassBeginInfo.clearValueCount = 1;
	vkCmdBeginRenderPass(m_commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanCommandList::EndRenderPass()
{
	vkCmdEndRenderPass(m_commandBuffer);
}

void VulkanCommandList::SetViewport(float width, float height, float x, float y)
{
	VkViewport viewport = { x, y + height, width, height, 0.f, 1.f };
	vkCmdSetViewport(m_commandBuffer, 0, 1, &viewport);
}

void VulkanCommandList::SetScissor(uint32 width, uint32 height, uint32 x, uint32 y)
{
	VkRect2D rect;
	rect.offset.x = x;
	rect.offset.y = y;
	rect.extent.width = width;
	rect.extent.height = height;
	vkCmdSetScissor(m_commandBuffer, 0, 1, &rect);
}

void VulkanCommandList::SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingStart)
{
	auto* pVulkanVertexBuffer = static_cast<VulkanBuffer*>(pVertexBuffer);

	VkDeviceSize offset[] = { 0 };
	vkCmdBindVertexBuffers(m_commandBuffer, bindingStart, 1, pVulkanVertexBuffer->GetAddressOf(), offset);
}

void VulkanCommandList::SetVertexBuffers(const Vector<IRHIBuffer*>& vertexBuffers, uint32 bindingStart)
{
	constexpr uint64 MaxVertexBufferCount = 4;
	assert(vertexBuffers.size() <= MaxVertexBufferCount);

	uint32 bufferCount = 0;
	VkBuffer buffer[MaxVertexBufferCount];
	for (auto* pVertexBuffer : vertexBuffers)
	{
		buffer[bufferCount] = static_cast<VulkanBuffer*>(pVertexBuffer)->GetHandle();
		++bufferCount;
	}

	VkDeviceSize offset[] = { 0 };
	vkCmdBindVertexBuffers(m_commandBuffer, bindingStart, bufferCount, buffer, offset);
}

void VulkanCommandList::SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16)
{
	auto* pVulkanIndexBuffer = static_cast<VulkanBuffer*>(pIndexBuffer);

	vkCmdBindIndexBuffer(m_commandBuffer, pVulkanIndexBuffer->GetHandle(), 0, useUInt16 ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32);
}

void VulkanCommandList::Draw(uint32 vertexCount, uint32 vertexStart)
{
	vkCmdDraw(m_commandBuffer, vertexCount, 1, vertexStart, 0);
}

void VulkanCommandList::DrawInstanced(uint32 vertexCount, uint32 vertexStart, uint32 instanceCount, uint32 instanceStart)
{
	vkCmdDraw(m_commandBuffer, vertexCount, instanceCount, vertexStart, instanceStart);
}

void VulkanCommandList::DrawIndexed(uint32 indexCount, uint32 indexStart, uint32_t vertexOffset)
{
	vkCmdDrawIndexed(m_commandBuffer, indexCount, 1, indexStart, vertexOffset, 0);
}

void VulkanCommandList::DrawIndexedInstanced(uint32 indexCount, uint32 instanceCount, uint32 indexStart, uint32 instanceStart, uint32_t vertexOffset)
{
	vkCmdDrawIndexed(m_commandBuffer, indexCount, instanceCount, indexStart, vertexOffset, instanceStart);
}

}