#include "VulkanTypes.h"

namespace ow
{

GPUAdapterType VulkanTypes::ToRHI(VkPhysicalDeviceType vkType)
{
    switch (vkType)
    {
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
        return GPUAdapterType::Discrete;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
        return GPUAdapterType::Integrated;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
        return GPUAdapterType::Virtual;
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
    default:
        return GPUAdapterType::CPU;
    }
}

VkSamplerAddressMode VulkanTypes::ToVK(RHIAddressMode rhiType)
{
    switch (rhiType)
    {
    case RHIAddressMode::Repeat:
        return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case RHIAddressMode::RepeatMirrored:
        return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    case RHIAddressMode::ClampToEdge:
        return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case RHIAddressMode::ClampToBorder:
        return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    case RHIAddressMode::MirrorClampToEdge:
        return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
    default:
        return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    }
}

VkBufferUsageFlags VulkanTypes::ToVK(RHIBufferUsage rhiType)
{
    switch (rhiType)
    {
    case RHIBufferUsage::VertexBuffer:
        return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    case RHIBufferUsage::IndexBuffer:
        return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    case RHIBufferUsage::UniformBuffer:
        return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    case RHIBufferUsage::StorageBuffer:
        return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    case RHIBufferUsage::IndirectBuffer:
        return VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    case RHIBufferUsage::TransferSource:
        return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    case RHIBufferUsage::TransferTarget:
        return VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    case RHIBufferUsage::TransformFeedbackBuffer:
        return VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT;
    case RHIBufferUsage::TransformFeedbackCounterBuffer:
        return VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT;
    default:
        return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    }
}

VkColorSpaceKHR VulkanTypes::ToVK(RHIColorSpace rhiType)
{
    switch (rhiType)
    {
    case RHIColorSpace::SRGB_NONLINEAR:
        return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    case RHIColorSpace::DISPLAY_P3_LINEAR:
        return VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT;
    case RHIColorSpace::DISPLAY_P3_NONLINEAR:
        return VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT;
    case RHIColorSpace::DCI_P3_LINEAR:
        return VK_COLOR_SPACE_DCI_P3_LINEAR_EXT;
    case RHIColorSpace::DCI_P3_NONLINEAR:
        return VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT;
    case RHIColorSpace::BT709_LINEAR:
        return VK_COLOR_SPACE_BT709_LINEAR_EXT;
    case RHIColorSpace::BT709_NONLINEAR:
        return VK_COLOR_SPACE_BT709_NONLINEAR_EXT;
    case RHIColorSpace::BT2020_LINEAR:
        return VK_COLOR_SPACE_BT2020_LINEAR_EXT;
    case RHIColorSpace::HDR10_ST2084:
        return VK_COLOR_SPACE_HDR10_ST2084_EXT;
    case RHIColorSpace::HDR10_HLG:
        return VK_COLOR_SPACE_HDR10_HLG_EXT;
    case RHIColorSpace::DOLBYVISION:
        return VK_COLOR_SPACE_DOLBYVISION_EXT;
    case RHIColorSpace::ADOBERGB_LINEAR:
        return VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT;
    case RHIColorSpace::ADOBERGB_NONLINEAR:
        return VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT;
    default:
        return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    }
}

VkCullModeFlagBits VulkanTypes::ToVK(RHICullMode rhiType)
{
    switch (rhiType)
    {
    case RHICullMode::None:
        return VK_CULL_MODE_NONE;
    case RHICullMode::Front:
        return VK_CULL_MODE_FRONT_BIT;
    case RHICullMode::Back:
        return VK_CULL_MODE_BACK_BIT;
    default:
        return VK_CULL_MODE_NONE;
    }
}

VkFilter VulkanTypes::ToVK(RHIFilter rhiType)
{
    switch (rhiType)
    {
    case RHIFilter::Linear:
        return VK_FILTER_LINEAR;
    case RHIFilter::Nearst:
        return VK_FILTER_NEAREST;
    case RHIFilter::Cubic:
        return VK_FILTER_CUBIC_IMG;
    default:
        return VK_FILTER_LINEAR;
    }
}

VkFormat VulkanTypes::ToVK(RHIFormat rhiType)
{
    switch (rhiType)
    {
    case RHIFormat::R8_UINT:
        return VK_FORMAT_R8_UINT;
    case RHIFormat::R8_SINT:
        return VK_FORMAT_R8_SINT;
    case RHIFormat::R8_UNORM:
        return VK_FORMAT_R8_UNORM;
    case RHIFormat::R8_SNORM:
        return VK_FORMAT_R8_SNORM;
    case RHIFormat::R16_UINT:
        return VK_FORMAT_R16_UINT;
    case RHIFormat::R16_SINT:
        return VK_FORMAT_R16_SINT;
    case RHIFormat::R16_UNORM:
        return VK_FORMAT_R16_UNORM;
    case RHIFormat::R16_SNORM:
        return VK_FORMAT_R16_SNORM;
    case RHIFormat::R16_FLOAT:
        return VK_FORMAT_R16_SFLOAT;
    case RHIFormat::R32_UINT:
        return VK_FORMAT_R32_UINT;
    case RHIFormat::R32_SINT:
        return VK_FORMAT_R32_SINT;
    case RHIFormat::R32_FLOAT:
        return VK_FORMAT_R32_SFLOAT;
    case RHIFormat::RG8_UINT:
        return VK_FORMAT_R8G8_UINT;
    case RHIFormat::RG8_SINT:
        return VK_FORMAT_R8G8_SINT;
    case RHIFormat::RG8_UNORM:
        return VK_FORMAT_R8G8_UNORM;
    case RHIFormat::RG8_SNORM:
        return VK_FORMAT_R8G8_SNORM;
    case RHIFormat::RG16_UINT:
        return VK_FORMAT_R16G16_UINT;
    case RHIFormat::RG16_SINT:
        return VK_FORMAT_R16G16_SINT;
    case RHIFormat::RG16_UNORM:
        return VK_FORMAT_R16G16_UNORM;
    case RHIFormat::RG16_SNORM:
        return VK_FORMAT_R16G16_SNORM;
    case RHIFormat::RG16_FLOAT:
        return VK_FORMAT_R16G16_SFLOAT;
    case RHIFormat::RG32_UINT:
        return VK_FORMAT_R32G32_UINT;
    case RHIFormat::RG32_SINT:
        return VK_FORMAT_R32G32_SINT;
    case RHIFormat::RG32_FLOAT:
        return VK_FORMAT_R32G32_SFLOAT;
    case RHIFormat::B5G6R5_UNORM:
        return VK_FORMAT_B5G6R5_UNORM_PACK16;
    case RHIFormat::BGRA4_UNORM:
        return VK_FORMAT_B4G4R4A4_UNORM_PACK16;
    case RHIFormat::B5G5R5A1_UNORM:
        return VK_FORMAT_B5G5R5A1_UNORM_PACK16;
    case RHIFormat::BGRA8_UNORM:
        return VK_FORMAT_B8G8R8A8_UNORM;
    case RHIFormat::BGRA8_UNORM_SRGB:
        return VK_FORMAT_B8G8R8A8_SRGB;
    case RHIFormat::RGB32_UINT:
        return VK_FORMAT_R32G32B32_UINT;
    case RHIFormat::RGB32_SINT:
        return VK_FORMAT_R32G32B32_SINT;
    case RHIFormat::RGB32_FLOAT:
        return VK_FORMAT_R32G32B32_SFLOAT;
    case RHIFormat::RGBA8_UINT:
        return VK_FORMAT_R8G8B8A8_UINT;
    case RHIFormat::RGBA8_SINT:
        return VK_FORMAT_R8G8B8A8_SINT;
    case RHIFormat::RGBA8_UNORM:
        return VK_FORMAT_R8G8B8A8_UNORM;
    case RHIFormat::RGBA8_UNORM_SRGB:
        return VK_FORMAT_R8G8B8A8_SRGB;
    case RHIFormat::RGBA8_SNORM:
        return VK_FORMAT_R8G8B8A8_SNORM;
    case RHIFormat::RGB10A2_UINT:
        return VK_FORMAT_A2R10G10B10_UINT_PACK32;
    case RHIFormat::RGB10A2_UNORM:
        return VK_FORMAT_A2R10G10B10_UNORM_PACK32;
    case RHIFormat::RGBA16_UINT:
        return VK_FORMAT_R16G16B16A16_UINT;
    case RHIFormat::RGBA16_SINT:
        return VK_FORMAT_R16G16B16A16_SINT;
    case RHIFormat::RGBA16_UNORM:
        return VK_FORMAT_R16G16B16A16_UNORM;
    case RHIFormat::RGBA16_SNORM:
        return VK_FORMAT_R16G16B16A16_SNORM;
    case RHIFormat::RGBA32_UINT:
        return VK_FORMAT_R32G32B32A32_UINT;
    case RHIFormat::RGBA32_SINT:
        return VK_FORMAT_R32G32B32A32_SINT;
    case RHIFormat::RGBA32_FLOAT:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    case RHIFormat::D16_UNORM:
        return VK_FORMAT_D16_UNORM;
    case RHIFormat::D24_UNORM_S8_UINT:
        return VK_FORMAT_D24_UNORM_S8_UINT;
    case RHIFormat::D32_FLOAT:
        return VK_FORMAT_D32_SFLOAT;
    case RHIFormat::D32_FLOAT_S8X24_UINT:
        return VK_FORMAT_D32_SFLOAT_S8_UINT;
    case RHIFormat::BC1_UNORM:
        return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
    case RHIFormat::BC1_UNORM_SRGB:
        return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
    case RHIFormat::BC2_UNORM:
        return VK_FORMAT_BC2_UNORM_BLOCK;
    case RHIFormat::BC2_UNORM_SRGB:
        return VK_FORMAT_BC2_SRGB_BLOCK;
    case RHIFormat::BC3_UNORM:
        return VK_FORMAT_BC3_UNORM_BLOCK;
    case RHIFormat::BC3_UNORM_SRGB:
        return VK_FORMAT_BC3_SRGB_BLOCK;
    case RHIFormat::BC4_UNORM:
        return VK_FORMAT_BC4_UNORM_BLOCK;
    case RHIFormat::BC4_SNORM:
        return VK_FORMAT_BC4_SNORM_BLOCK;
    case RHIFormat::BC5_UNORM:
        return VK_FORMAT_BC5_UNORM_BLOCK;
    case RHIFormat::BC5_SNORM:
        return VK_FORMAT_BC5_SNORM_BLOCK;
    case RHIFormat::BC6H_UFLOAT:
        return VK_FORMAT_BC6H_UFLOAT_BLOCK;
    case RHIFormat::BC6H_SFLOAT:
        return VK_FORMAT_BC6H_SFLOAT_BLOCK;
    case RHIFormat::BC7_UNORM:
        return VK_FORMAT_BC7_UNORM_BLOCK;
    case RHIFormat::BC7_UNORM_SRGB:
        return VK_FORMAT_BC7_SRGB_BLOCK;
    case RHIFormat::ASTC_4x4_UNORM:
        return VK_FORMAT_ASTC_4x4_UNORM_BLOCK;
    case RHIFormat::ASTC_4x4_UNORM_SRGB:
        return VK_FORMAT_ASTC_4x4_SRGB_BLOCK;
    case RHIFormat::ASTC_4x4_FLOAT:
        return VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK;
    case RHIFormat::ASTC_5x4_UNORM:
        return VK_FORMAT_ASTC_5x4_UNORM_BLOCK;
    case RHIFormat::ASTC_5x4_UNORM_SRGB:
        return VK_FORMAT_ASTC_5x4_SRGB_BLOCK;
    case RHIFormat::ASTC_5x4_FLOAT:
        return VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK;
    case RHIFormat::ASTC_5x5_UNORM:
        return VK_FORMAT_ASTC_5x5_UNORM_BLOCK;
    case RHIFormat::ASTC_5x5_UNORM_SRGB:
        return VK_FORMAT_ASTC_5x5_SRGB_BLOCK;
    case RHIFormat::ASTC_5x5_FLOAT:
        return VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK;
    case RHIFormat::ASTC_6x5_UNORM:
        return VK_FORMAT_ASTC_6x5_UNORM_BLOCK;
    case RHIFormat::ASTC_6x5_UNORM_SRGB:
        return VK_FORMAT_ASTC_6x5_SRGB_BLOCK;
    case RHIFormat::ASTC_6x5_FLOAT:
        return VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK;
    case RHIFormat::ASTC_6x6_UNORM:
        return VK_FORMAT_ASTC_6x6_UNORM_BLOCK;
    case RHIFormat::ASTC_6x6_UNORM_SRGB:
        return VK_FORMAT_ASTC_6x6_SRGB_BLOCK;
    case RHIFormat::ASTC_6x6_FLOAT:
        return VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK;
    case RHIFormat::ASTC_8x5_UNORM:
        return VK_FORMAT_ASTC_8x5_UNORM_BLOCK;
    case RHIFormat::ASTC_8x5_UNORM_SRGB:
        return VK_FORMAT_ASTC_8x5_SRGB_BLOCK;
    case RHIFormat::ASTC_8x5_FLOAT:
        return VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK;
    case RHIFormat::ASTC_8x6_UNORM:
        return VK_FORMAT_ASTC_8x6_UNORM_BLOCK;
    case RHIFormat::ASTC_8x6_UNORM_SRGB:
        return VK_FORMAT_ASTC_8x6_SRGB_BLOCK;
    case RHIFormat::ASTC_8x6_FLOAT:
        return VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK;
    case RHIFormat::ASTC_8x8_UNORM:
        return VK_FORMAT_ASTC_8x8_UNORM_BLOCK;
    case RHIFormat::ASTC_8x8_UNORM_SRGB:
        return VK_FORMAT_ASTC_8x8_SRGB_BLOCK;
    case RHIFormat::ASTC_8x8_FLOAT:
        return VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK;
    case RHIFormat::ASTC_10x5_UNORM:
        return VK_FORMAT_ASTC_10x5_UNORM_BLOCK;
    case RHIFormat::ASTC_10x5_UNORM_SRGB:
        return VK_FORMAT_ASTC_10x5_SRGB_BLOCK;
    case RHIFormat::ASTC_10x5_FLOAT:
        return VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK;
    case RHIFormat::ASTC_10x6_UNORM:
        return VK_FORMAT_ASTC_10x6_UNORM_BLOCK;
    case RHIFormat::ASTC_10x6_UNORM_SRGB:
        return VK_FORMAT_ASTC_10x6_SRGB_BLOCK;
    case RHIFormat::ASTC_10x6_FLOAT:
        return VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK;
    case RHIFormat::ASTC_10x8_UNORM:
        return VK_FORMAT_ASTC_10x8_UNORM_BLOCK;
    case RHIFormat::ASTC_10x8_UNORM_SRGB:
        return VK_FORMAT_ASTC_10x8_SRGB_BLOCK;
    case RHIFormat::ASTC_10x8_FLOAT:
        return VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK;
    case RHIFormat::ASTC_10x10_UNORM:
        return VK_FORMAT_ASTC_10x10_UNORM_BLOCK;
    case RHIFormat::ASTC_10x10_UNORM_SRGB:
        return VK_FORMAT_ASTC_10x10_SRGB_BLOCK;
    case RHIFormat::ASTC_10x10_FLOAT:
        return VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK;
    case RHIFormat::ASTC_12x10_UNORM:
        return VK_FORMAT_ASTC_12x10_UNORM_BLOCK;
    case RHIFormat::ASTC_12x10_UNORM_SRGB:
        return VK_FORMAT_ASTC_12x10_SRGB_BLOCK;
    case RHIFormat::ASTC_12x10_FLOAT:
        return VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK;
    case RHIFormat::ASTC_12x12_UNORM:
        return VK_FORMAT_ASTC_12x12_UNORM_BLOCK;
    case RHIFormat::ASTC_12x12_UNORM_SRGB:
        return VK_FORMAT_ASTC_12x12_SRGB_BLOCK;
    case RHIFormat::ASTC_12x12_FLOAT:
        return VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK;
    case RHIFormat::Unknown:
    default:
        return VK_FORMAT_UNDEFINED;
    }
}

VkFrontFace VulkanTypes::ToVK(RHIFrontFace rhiType)
{
    switch (rhiType)
    {
    case RHIFrontFace::Clockwise:
        return VK_FRONT_FACE_CLOCKWISE;
    case RHIFrontFace::CounterClockwise:
        return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    default:
        return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    }
}

VkSamplerMipmapMode VulkanTypes::ToVK(RHIMipmapMode rhiType)
{
    switch (rhiType)
    {
    case RHIMipmapMode::Linear:
        return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    case RHIMipmapMode::Nearst:
        return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    default:
        return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    }
}

VkPolygonMode VulkanTypes::ToVK(RHIPolygonMode rhiType)
{
    switch (rhiType)
    {
    case RHIPolygonMode::Solid:
        return VK_POLYGON_MODE_FILL;
    case RHIPolygonMode::Wireframe:
        return VK_POLYGON_MODE_LINE;
    default:
        return VK_POLYGON_MODE_FILL;
    }
}

VkPrimitiveTopology VulkanTypes::ToVK(RHIPrimitiveTopology rhiType)
{
    switch (rhiType)
    {
    case RHIPrimitiveTopology::PointList:
        return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case RHIPrimitiveTopology::LineList:
        return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case RHIPrimitiveTopology::LineStrip:
        return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case RHIPrimitiveTopology::TriangleList:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case RHIPrimitiveTopology::TriangleStrip:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    case RHIPrimitiveTopology::TriangleFan:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
    case RHIPrimitiveTopology::PatchList:
        return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
    default:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    }
}

VkShaderStageFlagBits VulkanTypes::ToVK(RHIShaderStage rhiType)
{
    switch (rhiType)
    {
    case RHIShaderStage::Vertex:
        return VK_SHADER_STAGE_VERTEX_BIT;
    case RHIShaderStage::Fragment:
        return VK_SHADER_STAGE_FRAGMENT_BIT;
    case RHIShaderStage::Compute:
        return VK_SHADER_STAGE_COMPUTE_BIT;
    case RHIShaderStage::RayGen:
        return VK_SHADER_STAGE_RAYGEN_BIT_KHR;
    case RHIShaderStage::AnyHit:
        return VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
    case RHIShaderStage::ClosestHit:
        return VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
    case RHIShaderStage::Miss:
        return VK_SHADER_STAGE_MISS_BIT_KHR;
    case RHIShaderStage::Intersection:
        return VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
    case RHIShaderStage::Callable:
        return VK_SHADER_STAGE_CALLABLE_BIT_KHR;
    case RHIShaderStage::Mesh:
        return VK_SHADER_STAGE_MESH_BIT_EXT;
    case RHIShaderStage::Task:
        return VK_SHADER_STAGE_TASK_BIT_EXT;
    default:
        return VK_SHADER_STAGE_ALL_GRAPHICS;
    }
}

VkImageViewType VulkanTypes::ToVK(RHITextureType rhiType)
{
    switch (rhiType)
    {
    case RHITextureType::Texture1D:
        return VK_IMAGE_VIEW_TYPE_1D;
    case RHITextureType::Texture2D:
        return VK_IMAGE_VIEW_TYPE_2D;
    case RHITextureType::Texture3D:
        return VK_IMAGE_VIEW_TYPE_3D;
    case RHITextureType::Texture1DArray:
        return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
    case RHITextureType::Texture2DArray:
        return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    case RHITextureType::TextureCube:
        return VK_IMAGE_VIEW_TYPE_CUBE;
    case RHITextureType::TextureCubeArray:
        return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
    default:
        return VK_IMAGE_VIEW_TYPE_2D;
    }
}

VkImageUsageFlags VulkanTypes::ToVK(RHITextureUsage rhiType)
{
    switch (rhiType)
    {
    case RHITextureUsage::SampledTexture:
        return VK_IMAGE_USAGE_SAMPLED_BIT;
    case RHITextureUsage::StorageTexture:
        return VK_IMAGE_USAGE_STORAGE_BIT;
    case RHITextureUsage::TransferSource:
        return VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    case RHITextureUsage::TransferTarget:
        return VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    default:
        return VK_IMAGE_VIEW_TYPE_2D;
    }
}

}