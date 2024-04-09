#include "VulkanSwapChain.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanSwapChain::VulkanSwapChain(VkSwapchainKHR swapChain) :
	m_swapChain(swapChain)
{
}

VulkanSwapChain::~VulkanSwapChain()
{
}

}