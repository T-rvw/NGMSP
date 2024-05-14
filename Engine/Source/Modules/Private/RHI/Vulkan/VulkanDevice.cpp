#include "VulkanDevice.h"

#include "VulkanAdapter.h"
#include "VulkanBarrier.h"
#include "VulkanBuffer.h"
#include "VulkanCommandPool.h"
#include "VulkanCommandQueue.h"
#include "VulkanFence.h"
#include "VulkanPipelineLayout.h"
#include "VulkanPipelineState.h"
#include "VulkanInstance.h"
#include "VulkanSemaphore.h"
#include "VulkanSwapChain.h"
#include "VulkanTexture.h"

#include <RHI/IRHICommandQueue.h>
#include <RHI/IRHIInstance.h>

namespace ow
{

namespace
{

struct VulkanAdapterRayTracing
{
	VulkanAdapterRayTracing()
	{
		ExtensionNames =
		{
			VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
			VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME, // required by VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME
			VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
			VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME, // required by VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME
			VK_KHR_RAY_QUERY_EXTENSION_NAME
		};

		AccelerateStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
		RayTracingPipelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
		RayQueryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
		AccelerateStructureFeatures.pNext = &RayTracingPipelineFeatures;
		RayTracingPipelineFeatures.pNext = &RayQueryFeatures;

		AccelerateStructureProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
		RayTracingPipelineProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
		AccelerateStructureProperties.pNext = &RayTracingPipelineProperties;
	}

	void AppendFeatures(void** pNextChain)
	{
		*pNextChain = &RayQueryFeatures;
		pNextChain = &RayQueryFeatures.pNext;
	}

	void AppendProperties(void** pNextChain)
	{
		*pNextChain = &RayTracingPipelineProperties;
		pNextChain = &RayTracingPipelineProperties.pNext;
	}

	Vector<const char*> ExtensionNames;

	VkPhysicalDeviceAccelerationStructureFeaturesKHR AccelerateStructureFeatures = {};
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR RayTracingPipelineFeatures = {};
	VkPhysicalDeviceRayQueryFeaturesKHR RayQueryFeatures = {};

	VkPhysicalDeviceAccelerationStructurePropertiesKHR AccelerateStructureProperties = {};
	VkPhysicalDeviceRayTracingPipelinePropertiesKHR RayTracingPipelineProperties = {};
};

struct VulkanAdapterMeshShader
{
	VulkanAdapterMeshShader()
	{
		ExtensionNames =
		{
			VK_EXT_MESH_SHADER_EXTENSION_NAME
		};

		MeshShaderFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;

		MeshShaderProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
	}

	void AppendFeatures(void** pNextChain)
	{
		*pNextChain = &MeshShaderFeatures;
		pNextChain = &MeshShaderFeatures.pNext;
	}

	void AppendProperties(void** pNextChain)
	{
		*pNextChain = &MeshShaderProperties;
		pNextChain = &MeshShaderProperties.pNext;
	}

	Vector<const char*> ExtensionNames;

	VkPhysicalDeviceMeshShaderFeaturesEXT MeshShaderFeatures = {};

	VkPhysicalDeviceMeshShaderPropertiesEXT MeshShaderProperties = {};
};

}

VulkanDevice::VulkanDevice(const VulkanAdapter* pAdapter, const RHIDeviceCreateInfo& createInfo) :
	m_pAdapter(pAdapter)
{
	auto* adapterFeatures = m_pAdapter->GetFeatures();
	auto* adapterProperties = m_pAdapter->GetProperties();

	// Enable extra extensions/features/properties by requirement.
	Vector<const char*> enabledExtensions =
	{
		VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME
	};

	{
		void** pFeaturesNextChain = &adapterFeatures->pNextChain;
		void** pPropertiesNextChain = &adapterProperties->pNextChain;

		auto requiredFeatrues = createInfo.Features;
		if (!requiredFeatrues.IsEnabled(RHIFeatures::Headless))
		{
			Assert(VulkanUtils::EnableExtensionSafely(enabledExtensions, m_pAdapter->GetAvailableExtensions(), VK_KHR_SWAPCHAIN_EXTENSION_NAME));
		}

		VulkanAdapterRayTracing rayTracing;
		if (requiredFeatrues.IsEnabled(RHIFeatures::RayTracing) &&
			VulkanUtils::EnableExtensionsSafely(enabledExtensions, m_pAdapter->GetAvailableExtensions(), rayTracing.ExtensionNames))
		{
			rayTracing.AppendFeatures(pFeaturesNextChain);
			rayTracing.AppendProperties(pPropertiesNextChain);
		}

		VulkanAdapterMeshShader meshShader;
		if (requiredFeatrues.IsEnabled(RHIFeatures::MeshShaders) &&
			VulkanUtils::EnableExtensionsSafely(enabledExtensions, m_pAdapter->GetAvailableExtensions(), meshShader.ExtensionNames))
		{
			meshShader.AppendFeatures(pFeaturesNextChain);
			meshShader.AppendProperties(pPropertiesNextChain);
		}

		vkGetPhysicalDeviceFeatures2(m_pAdapter->GetHandle(), &adapterFeatures->Features);
		vkGetPhysicalDeviceProperties2(m_pAdapter->GetHandle(), &adapterProperties->Properties);
	}

	constexpr uint32 commandTypeCount = EnumCount<RHICommandType>();
	Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	for (uint32 typeIndex = 0; typeIndex < commandTypeCount; ++typeIndex)
	{
		auto commandType = static_cast<RHICommandType>(typeIndex);
		if (!createInfo.CommandQueueTypes.IsEnabled(commandType))
		{
			continue;
		}

		const RHICommandQueueCreateInfo& commandQueueCI = m_pAdapter->GetCommandQueueCreateInfo(commandType);
		VkDeviceQueueCreateInfo& queueCreateInfo = queueCreateInfos.emplace_back();
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = commandQueueCI.FamilyIndex;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &commandQueueCI.Priority;
	}

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32>(queueCreateInfos.size());
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
	deviceCreateInfo.pEnabledFeatures = nullptr;
	deviceCreateInfo.pNext = &adapterFeatures->Features;
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32>(enabledExtensions.size());
	deviceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();

	VK_VERIFY(vkCreateDevice(m_pAdapter->GetHandle(), &deviceCreateInfo, nullptr, &m_device));
	Assert(m_device != VK_NULL_HANDLE);
	volkLoadDevice(m_device);

	for (uint32 typeIndex = 0; typeIndex < commandTypeCount; ++typeIndex)
	{
		auto commandType = static_cast<RHICommandType>(typeIndex);
		if (!createInfo.CommandQueueTypes.IsEnabled(commandType))
		{
			continue;
		}

		const RHICommandQueueCreateInfo& commandQueueCI = m_pAdapter->GetCommandQueueCreateInfo(commandType);
		m_commandQueues[typeIndex] = MakeRefCountPtr<VulkanCommandQueue>(this, commandQueueCI);
	}
}

VulkanDevice::~VulkanDevice()
{
	vkDestroyDevice(m_device, nullptr);
}

VkPhysicalDevice VulkanDevice::GetAdapter() const
{
	return m_pAdapter->GetHandle();
}

VkInstance VulkanDevice::GetInstance() const
{
	return m_pAdapter->GetInstance();
}

BarrierHandle VulkanDevice::CreateBarrier(const RHIBarrierCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanBarrier>(this, createInfo);
}

BufferHandle VulkanDevice::CreateBuffer(const RHIBufferCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanBuffer>(this, createInfo);
}

CommandPoolHandle VulkanDevice::CreateCommandPool(const RHICommandPoolCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanCommandPool>(this, createInfo);
}

FenceHandle VulkanDevice::CreateFence(const RHIFenceCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanFence>(this, createInfo);
}

PipelineLayoutHandle VulkanDevice::CreatePipelineLayout(const RHIPipelineLayoutCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanPipelineLayout>(this, createInfo);
}

PipelineStateHandle VulkanDevice::CreateComputePipelineState(const RHIComputePipelineStateCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanPipelineState>(this, createInfo);
}

PipelineStateHandle VulkanDevice::CreateGraphicsPipelineState(const RHIGraphicsPipelineStateCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanPipelineState>(this, createInfo);
}

PipelineStateHandle VulkanDevice::CreateRaytracingPipelineState(const RHIRaytracingPipelineStateCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanPipelineState>(this, createInfo);
}

SemaphoreHandle VulkanDevice::CreateSemaphore(const RHISemaphoreCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanSemaphore>(this, createInfo);
}

SwapChainHandle VulkanDevice::CreateSwapChain(const RHISwapChainCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanSwapChain>(this, createInfo);
}

TextureHandle VulkanDevice::CreateTexture(const RHITextureCreateInfo& createInfo)
{
	return MakeRefCountPtr<VulkanTexture>(this, createInfo);
}

CommandQueueHandle VulkanDevice::GetCommandQueue(RHICommandType commandType) const
{
	return m_commandQueues[static_cast<uint32>(commandType)];
}

}