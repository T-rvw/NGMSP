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

void VulkanCommandList::SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingSlot)
{
	auto* pVulkanVertexBuffer = static_cast<VulkanBuffer*>(pVertexBuffer);

	VkDeviceSize offset[] = { 0 };
	vkCmdBindVertexBuffers(m_commandBuffer, bindingSlot, 1, pVulkanVertexBuffer->GetAddressOf(), offset);
}

void VulkanCommandList::SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16)
{
	auto* pVulkanIndexBuffer = static_cast<VulkanBuffer*>(pIndexBuffer);

	vkCmdBindIndexBuffer(m_commandBuffer, pVulkanIndexBuffer->GetHandle(), 0, useUInt16 ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32);
}

void VulkanCommandList::SetViewport(const Viewport& viewport)
{
	auto vkViewport = VulkanTypes::ToVK(viewport);
	vkCmdSetViewport(m_commandBuffer, 0, 1, &vkViewport);
}

void VulkanCommandList::SetScissor(const Rect& rect)
{
	auto vkRect = VulkanTypes::ToVK(rect);
	vkCmdSetScissor(m_commandBuffer, 0, 1, &vkRect);
}

void VulkanCommandList::Dispath(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ)
{
	vkCmdDispatch(m_commandBuffer, threadGroupCountX, threadGroupCountY, threadGroupCountZ);
}

void VulkanCommandList::Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance)
{
	vkCmdDraw(m_commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

void VulkanCommandList::DrawIndirect(IRHIBuffer* pArgBuffer, uint32 offset, uint32 drawCount, uint32 stride)
{
	auto* pVulkanArgBuffer = static_cast<VulkanBuffer*>(pArgBuffer);
	vkCmdDrawIndirect(m_commandBuffer, pVulkanArgBuffer->GetHandle(), offset, drawCount, stride);
}

void VulkanCommandList::DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, uint32 vertexOffset, uint32 firstInstance)
{
	vkCmdDrawIndexed(m_commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

}