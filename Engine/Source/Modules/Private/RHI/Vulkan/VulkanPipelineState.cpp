#include "VulkanPipelineState.h"

#include "VulkanDevice.h"

#include <RHI/RHITypes.h>

namespace ow
{

VulkanPipelineState::VulkanPipelineState(const VulkanDevice* pDevice, const RHIComputePipelineStateCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkComputePipelineCreateInfo pipelineCI = {};
	pipelineCI.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	pipelineCI.stage;
	pipelineCI.layout;
	VK_VERIFY(vkCreateComputePipelines(m_pDevice->GetHandle(), nullptr, 1, &pipelineCI, nullptr, &m_pipelineState));
}

VulkanPipelineState::VulkanPipelineState(const VulkanDevice* pDevice, const RHIGraphicsPipelineStateCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	// Vertex Input
	VkPipelineVertexInputStateCreateInfo vertexInputStateCI = {};
	vertexInputStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputStateCI.pVertexAttributeDescriptions;
	vertexInputStateCI.vertexAttributeDescriptionCount;
	vertexInputStateCI.pVertexBindingDescriptions;
	vertexInputStateCI.vertexBindingDescriptionCount;

	// Input Assembly
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCI = {};
	inputAssemblyStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyStateCI.topology = VulkanTypes::ToVK(createInfo.Topology);

	// Viewport
	VkPipelineViewportStateCreateInfo viewportStateCI = {};
	viewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateCI.viewportCount = 1;
	viewportStateCI.scissorCount = 1;

	// Rasterization
	VkPipelineRasterizationStateCreateInfo rasterizationStateCI = {};
	rasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizationStateCI.polygonMode = VulkanTypes::ToVK(createInfo.PolygonMode);
	rasterizationStateCI.cullMode = VulkanTypes::ToVK(createInfo.CullMode);
	rasterizationStateCI.frontFace = VulkanTypes::ToVK(createInfo.FrontFace);
	rasterizationStateCI.rasterizerDiscardEnable = VK_TRUE;
	rasterizationStateCI.depthClampEnable = VK_TRUE;
	rasterizationStateCI.depthBiasEnable = VK_TRUE;
	rasterizationStateCI.depthBiasClamp = 1.0f;
	rasterizationStateCI.depthBiasSlopeFactor = 1.0f;
	rasterizationStateCI.lineWidth = 1.0f;

	// Multisample
	VkPipelineMultisampleStateCreateInfo multisampleStateCI = {};
	multisampleStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleStateCI.sampleShadingEnable;
	multisampleStateCI.rasterizationSamples;
	multisampleStateCI.minSampleShading;
	multisampleStateCI.alphaToCoverageEnable;
	multisampleStateCI.alphaToOneEnable;
	multisampleStateCI.pSampleMask;

	// DepthStencil
	VkPipelineDepthStencilStateCreateInfo depthStencilStateCI = {};
	depthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencilStateCI.depthTestEnable;
	depthStencilStateCI.depthWriteEnable;
	depthStencilStateCI.depthCompareOp;
	depthStencilStateCI.depthBoundsTestEnable;
	depthStencilStateCI.stencilTestEnable;
	depthStencilStateCI.front.failOp;
	depthStencilStateCI.front.passOp;
	depthStencilStateCI.front.depthFailOp;
	depthStencilStateCI.front.compareOp;
	depthStencilStateCI.front.compareMask = ~0U;
	depthStencilStateCI.front.writeMask = ~0U;
	depthStencilStateCI.front.reference = ~0U;
	depthStencilStateCI.back.failOp;
	depthStencilStateCI.back.passOp;
	depthStencilStateCI.back.depthFailOp;
	depthStencilStateCI.back.compareOp;
	depthStencilStateCI.back.compareMask = ~0U;
	depthStencilStateCI.back.writeMask = ~0U;
	depthStencilStateCI.back.reference = ~0U;

	// Blend
	VkPipelineColorBlendStateCreateInfo colorBlendStateCI = {};
	colorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendStateCI.logicOpEnable;
	colorBlendStateCI.logicOp;
	colorBlendStateCI.attachmentCount;
	colorBlendStateCI.pAttachments;
	colorBlendStateCI.blendConstants[0] = 1.0f;
	colorBlendStateCI.blendConstants[1] = 1.0f;
	colorBlendStateCI.blendConstants[2] = 1.0f;
	colorBlendStateCI.blendConstants[3] = 1.0f;

	// Dynamic
	constexpr VkDynamicState DynamicStates[] =
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
		VK_DYNAMIC_STATE_LINE_WIDTH,
		VK_DYNAMIC_STATE_DEPTH_BIAS,
		VK_DYNAMIC_STATE_BLEND_CONSTANTS,
		VK_DYNAMIC_STATE_DEPTH_BOUNDS,
		VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
		VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
		VK_DYNAMIC_STATE_STENCIL_REFERENCE
	};

	VkPipelineDynamicStateCreateInfo dynamicStateCI = {};
	dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicStateCI.pDynamicStates = DynamicStates;
	dynamicStateCI.dynamicStateCount = static_cast<uint32>(sizeof(DynamicStates) / sizeof(VkDynamicState));

	VkGraphicsPipelineCreateInfo pipelineCI = {};
	pipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	//pipelineCI.stageCount = vkb::to_u32(shader_stages.size());
	//pipelineCI.pStages = shader_stages.data();
	pipelineCI.pVertexInputState = &vertexInputStateCI;
	pipelineCI.pInputAssemblyState = &inputAssemblyStateCI;
	pipelineCI.pRasterizationState = &rasterizationStateCI;
	pipelineCI.pColorBlendState = &colorBlendStateCI;
	pipelineCI.pMultisampleState = &multisampleStateCI;
	pipelineCI.pViewportState = &viewportStateCI;
	pipelineCI.pDepthStencilState = &depthStencilStateCI;
	pipelineCI.pDynamicState = &dynamicStateCI;
	//pipelineCI.renderPass = context.render_pass;
	//pipelineCI.layout = context.pipeline_layout;
	VK_VERIFY(vkCreateGraphicsPipelines(m_pDevice->GetHandle(), VK_NULL_HANDLE, 1, &pipelineCI, nullptr, &m_pipelineState));
}

VulkanPipelineState::VulkanPipelineState(const VulkanDevice* pDevice, const RHIRaytracingPipelineStateCreateInfo& createInfo) :
	m_pDevice(pDevice)
{
	VkRayTracingPipelineCreateInfoKHR pipelineCI = {};
	pipelineCI.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
	pipelineCI.stageCount;
	pipelineCI.pStages;
	pipelineCI.groupCount;
	pipelineCI.pGroups;
	pipelineCI.maxPipelineRayRecursionDepth;
	pipelineCI.layout;
	VK_VERIFY(vkCreateRayTracingPipelinesKHR(m_pDevice->GetHandle(), VK_NULL_HANDLE, VK_NULL_HANDLE, 1, &pipelineCI, nullptr, &m_pipelineState));
}

VulkanPipelineState::~VulkanPipelineState()
{
	vkDestroyPipeline(m_pDevice->GetHandle(), m_pipelineState, nullptr);
}

}