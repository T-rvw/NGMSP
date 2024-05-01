#include "VulkanCommandQueue.h"

#include "VulkanCommandList.h"
#include "VulkanDevice.h"
#include "VulkanFence.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanCommandQueue::VulkanCommandQueue(const VulkanDevice* pDevice, const RHICommandQueueCreateInfo& createInfo) :
    m_familyIndex(createInfo.FamilyIndex)
{
    SetType(createInfo.Type);
	vkGetDeviceQueue(pDevice->GetHandle(), m_familyIndex, createInfo.QueueIndex, &m_commandQueue);
}

void VulkanCommandQueue::Submit(IRHIFence* pFence)
{
    auto* pVulkanFence = static_cast<VulkanFence*>(pFence);
    vkQueueSubmit(m_commandQueue, 0, nullptr, pVulkanFence->GetHandle());
}

void VulkanCommandQueue::Submit(IRHICommandList* pCommandBuffer, IRHIFence* pFence)
{
    auto* pVulkanCommandBuffer = static_cast<VulkanCommandList*>(pCommandBuffer);
    auto* pVulkanFence = static_cast<VulkanFence*>(pFence);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = pVulkanCommandBuffer->GetAddressOf();
    VK_VERIFY(vkQueueSubmit(m_commandQueue, 1, &submitInfo, pVulkanFence->GetHandle()));
}

void VulkanCommandQueue::Submit(IRHICommandList* pCommandBuffer, IRHIFence* pFence, IRHISemaphore* pWaitSemaphore, IRHISemaphore* pSignalSemaphore)
{
    auto* pVulkanCommandBuffer = static_cast<VulkanCommandList*>(pCommandBuffer);
    auto* pVulkanWaitSemaphore = static_cast<VulkanSemaphore*>(pWaitSemaphore);
    auto* pVulkanSignalSemaphore = static_cast<VulkanSemaphore*>(pSignalSemaphore);

    const VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = pVulkanWaitSemaphore->GetAddressOf();
    submitInfo.pWaitDstStageMask = &waitDstStageMask;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = pVulkanSignalSemaphore->GetAddressOf();
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = pVulkanCommandBuffer->GetAddressOf();
    VK_VERIFY(vkQueueSubmit(m_commandQueue, 1, &submitInfo, pFence ? static_cast<VulkanFence*>(pFence)->GetHandle() : VK_NULL_HANDLE));
}

}