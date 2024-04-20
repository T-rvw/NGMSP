#include "VulkanTypes.h"

namespace ow
{

GPUAdapterType VulkanTypes::ToRHI(VkPhysicalDeviceType vkType)
{
    switch (vkType)
    {
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
    {
        return GPUAdapterType::Discrete;
        break;
    }
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
    {
        return GPUAdapterType::Integrated;
        break;
    }
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
    {
        return GPUAdapterType::Virtual;
        break;
    }
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
    default:
    {
        return GPUAdapterType::CPU;
        break;
    }
    }

    return GPUAdapterType::CPU;
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
        assert("Unknow Vulkan format.");
        return VK_FORMAT_UNDEFINED;
    }
}

}