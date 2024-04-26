#include "VulkanCommandBuffer.h"

#include "VulkanBuffer.h"
#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanCommandPool* pCommandPool, const RHICommandBufferCreateInfo& createInfo)
{
	VkCommandBufferAllocateInfo commandBufferInfo {};
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferInfo.commandPool = pCommandPool->GetHandle();
	commandBufferInfo.commandBufferCount = 1;
	VK_VERIFY(vkAllocateCommandBuffers(pCommandPool->GetDevice()->GetHandle(), &commandBufferInfo, &m_commandBuffer));
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
}

void VulkanCommandBuffer::Begin()
{
	VkCommandBufferBeginInfo beginInfo {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	VK_VERIFY(vkBeginCommandBuffer(m_commandBuffer, &beginInfo));
}

void VulkanCommandBuffer::End()
{
	VK_VERIFY(vkEndCommandBuffer(m_commandBuffer));
}

void VulkanCommandBuffer::BeginRenderPass(IRHISwapChain* pSwapChain)
{
	auto* pVulkanSwapChain = static_cast<VulkanSwapChain*>(pSwapChain);
	uint32 backBufferIndex = pVulkanSwapChain->GetCurrentBackBufferIndex();

	VkClearValue clearValue {};
	clearValue.color.float32[0] = 0.0f;
	clearValue.color.float32[1] = 0.0f;
	clearValue.color.float32[2] = 0.0f;
	clearValue.color.float32[3] = 1.0f;

	VkRenderPassBeginInfo renderPassBeginInfo {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = pVulkanSwapChain->GetFrameBuffer(backBufferIndex);
	renderPassBeginInfo.renderArea.extent = pVulkanSwapChain->GetSwapChainExtent();
	renderPassBeginInfo.renderPass = pVulkanSwapChain->GetRenderPass();
	renderPassBeginInfo.pClearValues = &clearValue;
	renderPassBeginInfo.clearValueCount = 1;
	vkCmdBeginRenderPass(m_commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanCommandBuffer::EndRenderPass()
{
	vkCmdEndRenderPass(m_commandBuffer);
}

void VulkanCommandBuffer::SetViewport(float width, float height, float x, float y)
{
	VkViewport viewport = { x, y + height, width, height, 0.f, 1.f };
	vkCmdSetViewport(m_commandBuffer, 0, 1, &viewport);
}

void VulkanCommandBuffer::SetScissor(uint32 width, uint32 height, uint32 x, uint32 y)
{
	VkRect2D rect;
	rect.offset.x = x;
	rect.offset.y = y;
	rect.extent.width = width;
	rect.extent.height = height;
	vkCmdSetScissor(m_commandBuffer, 0, 1, &rect);
}

void VulkanCommandBuffer::SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingStart)
{
	auto* pVulkanVertexBuffer = static_cast<VulkanBuffer*>(pVertexBuffer);

	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(m_commandBuffer, bindingStart, 1, pVulkanVertexBuffer->GetAddressOf(), &offset);
}

void VulkanCommandBuffer::SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16)
{
	auto* pVulkanIndexBuffer = static_cast<VulkanBuffer*>(pIndexBuffer);

	vkCmdBindIndexBuffer(m_commandBuffer, pVulkanIndexBuffer->GetHandle(), 0, useUInt16 ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32);
}

void VulkanCommandBuffer::Draw(uint32 vertexCount, uint32 vertexStart, uint32 instanceCount, uint32 instanceStart)
{

}

void VulkanCommandBuffer::DrawIndexed(uint32 indexCount, uint32 indexStart, uint32_t vertexOffset, uint32 instanceCount, uint32 instanceStart)
{

}

}