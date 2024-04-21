#include "D3D12Types.h"

namespace ow
{

RHIColorSpace D3D12Types::ToRHI(DXGI_COLOR_SPACE_TYPE d3d12Type)
{
    switch (d3d12Type)
    {
    case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709:
        return RHIColorSpace::SRGB_NONLINEAR;
    case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020:
        return RHIColorSpace::DISPLAY_P3_LINEAR;
    case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709:
        return RHIColorSpace::DISPLAY_P3_NONLINEAR;
    case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601:
        return RHIColorSpace::DCI_P3_NONLINEAR;
    case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709:
        return RHIColorSpace::BT709_LINEAR;
    case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709:
        return RHIColorSpace::BT709_NONLINEAR;
    case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020:
        return RHIColorSpace::BT2020_LINEAR;
    case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
        return RHIColorSpace::HDR10_ST2084;
    case DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020:
        return RHIColorSpace::HDR10_HLG;
    case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020:
        return RHIColorSpace::DOLBYVISION;
    case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709:
        return RHIColorSpace::ADOBERGB_LINEAR;
    case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020:
        return RHIColorSpace::ADOBERGB_NONLINEAR;
    default:
        return RHIColorSpace::SRGB_NONLINEAR;
    }
}

D3D12_BLEND_OP D3D12Types::ToD3D12(RHIBlendOperation rhiType)
{
    switch (rhiType)
    {
    case RHIBlendOperation::Add:
        return D3D12_BLEND_OP_ADD;
    case RHIBlendOperation::Subtract:
        return D3D12_BLEND_OP_SUBTRACT;
    case RHIBlendOperation::Min:
        return D3D12_BLEND_OP_MIN;
    case RHIBlendOperation::Max:
        return D3D12_BLEND_OP_MAX;
    case RHIBlendOperation::RevSubtract:
        return D3D12_BLEND_OP_REV_SUBTRACT;
    default:
        return D3D12_BLEND_OP_ADD;
    }
}

D3D12_BLEND D3D12Types::ToD3D12(RHIBlendType rhiType)
{
    switch (rhiType)
    {
    case RHIBlendType::Zero:
        return D3D12_BLEND_ZERO;
    case RHIBlendType::One:
        return D3D12_BLEND_ONE;
    case RHIBlendType::SrcColor:
        return D3D12_BLEND_SRC_COLOR;
    case RHIBlendType::InvSrcColor:
        return D3D12_BLEND_INV_SRC_COLOR;
    case RHIBlendType::SrcAlpha:
        return D3D12_BLEND_SRC_ALPHA;
    case RHIBlendType::InvSrcAlpha:
        return D3D12_BLEND_INV_SRC_ALPHA;
    case RHIBlendType::DestAlpha:
        return D3D12_BLEND_DEST_ALPHA;
    case RHIBlendType::InvDestAlpha:
        return D3D12_BLEND_INV_DEST_ALPHA;
    case RHIBlendType::DestColor:
        return D3D12_BLEND_DEST_COLOR;
    case RHIBlendType::InvDestColor:
        return D3D12_BLEND_INV_DEST_COLOR;
    case RHIBlendType::SrcAlphaSat:
        return D3D12_BLEND_SRC_ALPHA_SAT;
    case RHIBlendType::BlendFactor:
        return D3D12_BLEND_BLEND_FACTOR;
    case RHIBlendType::InvBlendFactor:
        return D3D12_BLEND_INV_BLEND_FACTOR;
    case RHIBlendType::Src1Color:
        return D3D12_BLEND_SRC1_COLOR;
    case RHIBlendType::InvSrc1Color:
        return D3D12_BLEND_INV_SRC1_COLOR;
    case RHIBlendType::Src1Alpha:
        return D3D12_BLEND_SRC1_ALPHA;
    case RHIBlendType::InvSrc1Alpha:
        return D3D12_BLEND_INV_SRC1_ALPHA;
    default:
        return D3D12_BLEND_ZERO;
    }
}

DXGI_COLOR_SPACE_TYPE D3D12Types::ToD3D12(RHIColorSpace rhiType)
{
    switch (rhiType)
    {
    case RHIColorSpace::SRGB_NONLINEAR:
        return DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
    case RHIColorSpace::DISPLAY_P3_LINEAR:
        return DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020;
    case RHIColorSpace::DISPLAY_P3_NONLINEAR:
        return DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709;
    case RHIColorSpace::DCI_P3_LINEAR:
        return ToD3D12(RHIColorSpace::DISPLAY_P3_LINEAR);
    case RHIColorSpace::DCI_P3_NONLINEAR:
        return DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601;
    case RHIColorSpace::BT709_LINEAR:
        return DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709;
    case RHIColorSpace::BT709_NONLINEAR:
        return DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709;
    case RHIColorSpace::BT2020_LINEAR:
        return DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020;
    case RHIColorSpace::HDR10_ST2084:
        return DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;
    case RHIColorSpace::HDR10_HLG:
        return DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020;
    case RHIColorSpace::DOLBYVISION:
        return DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020;
    case RHIColorSpace::ADOBERGB_LINEAR:
        return DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709;
    case RHIColorSpace::ADOBERGB_NONLINEAR:
        return DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020;
    default:
        return DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
    }
}

D3D12_COMMAND_LIST_TYPE D3D12Types::ToD3D12(RHICommandType rhiType)
{
    switch (rhiType)
    {
    case RHICommandType::Graphics:
        return D3D12_COMMAND_LIST_TYPE_DIRECT;
    case RHICommandType::Compute:
        return D3D12_COMMAND_LIST_TYPE_COMPUTE;
    case RHICommandType::Copy:
        return D3D12_COMMAND_LIST_TYPE_COPY;
    default:
        return D3D12_COMMAND_LIST_TYPE_DIRECT;
    }
}

D3D12_CULL_MODE D3D12Types::ToD3D12(RHICullMode rhiType)
{
    switch (rhiType)
    {
    case RHICullMode::None:
        return D3D12_CULL_MODE_NONE;
    case RHICullMode::Front:
        return D3D12_CULL_MODE_FRONT;
    case RHICullMode::Back:
        return D3D12_CULL_MODE_BACK;
    default:
        return D3D12_CULL_MODE_NONE;
    }
}

D3D12_FENCE_FLAGS D3D12Types::ToD3D12(RHIFenceType rhiType)
{
    switch (rhiType)
    {
    case RHIFenceType::Default:
        return D3D12_FENCE_FLAG_NONE;
    case RHIFenceType::Shared:
        return D3D12_FENCE_FLAG_SHARED;
    case RHIFenceType::CrossAdapter:
        return D3D12_FENCE_FLAG_SHARED_CROSS_ADAPTER;
    default:
        return D3D12_FENCE_FLAG_NONE;
    }
}

DXGI_FORMAT D3D12Types::ToD3D12(RHIFormat rhiType)
{
    switch (rhiType)
    {
    case RHIFormat::R8_UINT:
        return DXGI_FORMAT_R8_UINT;
    case RHIFormat::R8_SINT:
        return DXGI_FORMAT_R8_SINT;
    case RHIFormat::R8_UNORM:
        return DXGI_FORMAT_R8_UNORM;
    case RHIFormat::R8_SNORM:
        return DXGI_FORMAT_R8_SNORM;
    case RHIFormat::R8_TYPELESS:
        return DXGI_FORMAT_R8_TYPELESS;
    case RHIFormat::R16_UINT:
        return DXGI_FORMAT_R16_UINT;
    case RHIFormat::R16_SINT:
        return DXGI_FORMAT_R16_SINT;
    case RHIFormat::R16_UNORM:
        return DXGI_FORMAT_R16_UNORM;
    case RHIFormat::R16_SNORM:
        return DXGI_FORMAT_R16_SNORM;
    case RHIFormat::R16_FLOAT:
        return DXGI_FORMAT_R16_FLOAT;
    case RHIFormat::R16_TYPELESS:
        return DXGI_FORMAT_R16_TYPELESS;
    case RHIFormat::R32_UINT:
        return DXGI_FORMAT_R32_UINT;
    case RHIFormat::R32_SINT:
        return DXGI_FORMAT_R32_SINT;
    case RHIFormat::R32_FLOAT:
        return DXGI_FORMAT_R32_FLOAT;
    case RHIFormat::R32_TYPELESS:
        return DXGI_FORMAT_R32_TYPELESS;
    case RHIFormat::RG8_UINT:
        return DXGI_FORMAT_R8G8_UINT;
    case RHIFormat::RG8_SINT:
        return DXGI_FORMAT_R8G8_SINT;
    case RHIFormat::RG8_UNORM:
        return DXGI_FORMAT_R8G8_UNORM;
    case RHIFormat::RG8_SNORM:
        return DXGI_FORMAT_R8G8_SNORM;
    case RHIFormat::RG8_TYPELESS:
        return DXGI_FORMAT_R8G8_TYPELESS;
    case RHIFormat::RG16_UINT:
        return DXGI_FORMAT_R16G16_UINT;
    case RHIFormat::RG16_SINT:
        return DXGI_FORMAT_R16G16_SINT;
    case RHIFormat::RG16_UNORM:
        return DXGI_FORMAT_R16G16_UNORM;
    case RHIFormat::RG16_SNORM:
        return DXGI_FORMAT_R16G16_SNORM;
    case RHIFormat::RG16_FLOAT:
        return DXGI_FORMAT_R16G16_FLOAT;
    case RHIFormat::RG16_TYPELESS:
        return DXGI_FORMAT_R16G16_TYPELESS;
    case RHIFormat::RG32_UINT:
        return DXGI_FORMAT_R32G32_UINT;
    case RHIFormat::RG32_SINT:
        return DXGI_FORMAT_R32G32_SINT;
    case RHIFormat::RG32_FLOAT:
        return DXGI_FORMAT_R32G32_FLOAT;
    case RHIFormat::RG32_TYPELESS:
        return DXGI_FORMAT_R32G32_TYPELESS;
    case RHIFormat::B5G6R5_UNORM:
        return DXGI_FORMAT_B5G6R5_UNORM;
    case RHIFormat::BGRA4_UNORM:
        return DXGI_FORMAT_B4G4R4A4_UNORM;
    case RHIFormat::B5G5R5A1_UNORM:
        return DXGI_FORMAT_B5G5R5A1_UNORM;
    case RHIFormat::BGRA8_UNORM:
        return DXGI_FORMAT_B8G8R8A8_UNORM;
    case RHIFormat::BGRA8_UNORM_SRGB:
        return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    case RHIFormat::BGRA8_TYPELESS:
        return DXGI_FORMAT_B8G8R8A8_TYPELESS;
    case RHIFormat::BGRX8_UNORM:
        return DXGI_FORMAT_B8G8R8X8_UNORM;
    case RHIFormat::BGRX8_UNORM_SRGB:
        return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
    case RHIFormat::BGRX8_TYPELESS:
        return DXGI_FORMAT_B8G8R8X8_TYPELESS;
    case RHIFormat::RGB32_UINT:
        return DXGI_FORMAT_R32G32B32_UINT;
    case RHIFormat::RGB32_SINT:
        return DXGI_FORMAT_R32G32B32_SINT;
    case RHIFormat::RGB32_FLOAT:
        return DXGI_FORMAT_R32G32B32_FLOAT;
    case RHIFormat::RGB32_TYPELESS:
        return DXGI_FORMAT_R32G32B32_TYPELESS;
    case RHIFormat::RGBA8_UINT:
        return DXGI_FORMAT_R8G8B8A8_UINT;
    case RHIFormat::RGBA8_SINT:
        return DXGI_FORMAT_R8G8B8A8_SINT;
    case RHIFormat::RGBA8_UNORM:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    case RHIFormat::RGBA8_UNORM_SRGB:
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    case RHIFormat::RGBA8_SNORM:
        return DXGI_FORMAT_R8G8B8A8_SNORM;
    case RHIFormat::RGBA8_TYPELESS:
        return DXGI_FORMAT_R8G8B8A8_TYPELESS;
    case RHIFormat::RGB10A2_UINT:
        return DXGI_FORMAT_R10G10B10A2_UINT;
    case RHIFormat::RGB10A2_UNORM:
        return DXGI_FORMAT_R10G10B10A2_UNORM;
    case RHIFormat::RGB10A2_TYPELESS:
        return DXGI_FORMAT_R10G10B10A2_TYPELESS;
    case RHIFormat::R11G11B10_FLOAT:
        return DXGI_FORMAT_R11G11B10_FLOAT;
    case RHIFormat::RGBA16_UINT:
        return DXGI_FORMAT_R16G16B16A16_UINT;
    case RHIFormat::RGBA16_SINT:
        return DXGI_FORMAT_R16G16B16A16_SINT;
    case RHIFormat::RGBA16_UNORM:
        return DXGI_FORMAT_R16G16B16A16_UNORM;
    case RHIFormat::RGBA16_SNORM:
        return DXGI_FORMAT_R16G16B16A16_SNORM;
    case RHIFormat::RGBA16_TYPELESS:
        return DXGI_FORMAT_R16G16B16A16_TYPELESS;
    case RHIFormat::RGBA32_UINT:
        return DXGI_FORMAT_R32G32B32A32_UINT;
    case RHIFormat::RGBA32_SINT:
        return DXGI_FORMAT_R32G32B32A32_SINT;
    case RHIFormat::RGBA32_FLOAT:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case RHIFormat::RGBA32_TYPELESS:
        return DXGI_FORMAT_R32G32B32A32_TYPELESS;
    case RHIFormat::D16_UNORM:
        return DXGI_FORMAT_D16_UNORM;
    case RHIFormat::D24_UNORM_S8_UINT:
        return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case RHIFormat::D32_FLOAT:
        return DXGI_FORMAT_D32_FLOAT;
    case RHIFormat::D32_FLOAT_S8X24_UINT:
        return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    case RHIFormat::BC1_UNORM:
        return DXGI_FORMAT_BC1_UNORM;
    case RHIFormat::BC1_UNORM_SRGB:
        return DXGI_FORMAT_BC1_UNORM_SRGB;
    case RHIFormat::BC1_TYPELESS:
        return DXGI_FORMAT_BC1_TYPELESS;
    case RHIFormat::BC2_UNORM:
        return DXGI_FORMAT_BC2_UNORM;
    case RHIFormat::BC2_UNORM_SRGB:
        return DXGI_FORMAT_BC2_UNORM_SRGB;
    case RHIFormat::BC2_TYPELESS:
        return DXGI_FORMAT_BC2_TYPELESS;
    case RHIFormat::BC3_UNORM:
        return DXGI_FORMAT_BC3_UNORM;
    case RHIFormat::BC3_UNORM_SRGB:
        return DXGI_FORMAT_BC3_UNORM_SRGB;
    case RHIFormat::BC3_TYPELESS:
        return DXGI_FORMAT_BC3_TYPELESS;
    case RHIFormat::BC4_UNORM:
        return DXGI_FORMAT_BC4_UNORM;
    case RHIFormat::BC4_SNORM:
        return DXGI_FORMAT_BC4_SNORM;
    case RHIFormat::BC4_TYPELESS:
        return DXGI_FORMAT_BC4_TYPELESS;
    case RHIFormat::BC5_UNORM:
        return DXGI_FORMAT_BC5_UNORM;
    case RHIFormat::BC5_SNORM:
        return DXGI_FORMAT_BC5_SNORM;
    case RHIFormat::BC5_TYPELESS:
        return DXGI_FORMAT_BC5_TYPELESS;
    case RHIFormat::BC6H_UFLOAT:
        return DXGI_FORMAT_BC6H_UF16;
    case RHIFormat::BC6H_SFLOAT:
        return DXGI_FORMAT_BC6H_SF16;
    case RHIFormat::BC6H_TYPELESS:
        return DXGI_FORMAT_BC6H_TYPELESS;
    case RHIFormat::BC7_UNORM:
        return DXGI_FORMAT_BC7_UNORM;
    case RHIFormat::BC7_UNORM_SRGB:
        return DXGI_FORMAT_BC7_UNORM_SRGB;
    case RHIFormat::BC7_TYPELESS:
        return DXGI_FORMAT_BC7_TYPELESS;
    case RHIFormat::ASTC_4x4_UNORM:
        return DXGI_FORMAT_ASTC_4X4_UNORM;
    case RHIFormat::ASTC_4x4_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_4X4_UNORM_SRGB;
    case RHIFormat::ASTC_4x4_TYPELESS:
        return DXGI_FORMAT_ASTC_4X4_TYPELESS;
    case RHIFormat::ASTC_5x4_UNORM:
        return DXGI_FORMAT_ASTC_5X4_UNORM;
    case RHIFormat::ASTC_5x4_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_5X4_UNORM_SRGB;
    case RHIFormat::ASTC_5x4_TYPELESS:
        return DXGI_FORMAT_ASTC_5X4_TYPELESS;
    case RHIFormat::ASTC_5x5_UNORM:
        return DXGI_FORMAT_ASTC_5X5_UNORM;
    case RHIFormat::ASTC_5x5_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_5X5_UNORM_SRGB;
    case RHIFormat::ASTC_5x5_TYPELESS:
        return DXGI_FORMAT_ASTC_5X5_TYPELESS;
    case RHIFormat::ASTC_6x5_UNORM:
        return DXGI_FORMAT_ASTC_6X5_UNORM;
    case RHIFormat::ASTC_6x5_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_6X5_UNORM_SRGB;
    case RHIFormat::ASTC_6x5_TYPELESS:
        return DXGI_FORMAT_ASTC_6X5_TYPELESS;
    case RHIFormat::ASTC_6x6_UNORM:
        return DXGI_FORMAT_ASTC_6X6_UNORM;
    case RHIFormat::ASTC_6x6_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_6X6_UNORM_SRGB;
    case RHIFormat::ASTC_6x6_TYPELESS:
        return DXGI_FORMAT_ASTC_6X6_TYPELESS;
    case RHIFormat::ASTC_8x5_UNORM:
        return DXGI_FORMAT_ASTC_8X5_UNORM;
    case RHIFormat::ASTC_8x5_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_8X5_UNORM_SRGB;
    case RHIFormat::ASTC_8x5_TYPELESS:
        return DXGI_FORMAT_ASTC_8X5_TYPELESS;
    case RHIFormat::ASTC_8x6_UNORM:
        return DXGI_FORMAT_ASTC_8X6_UNORM;
    case RHIFormat::ASTC_8x6_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_8X6_UNORM_SRGB;
    case RHIFormat::ASTC_8x6_TYPELESS:
        return DXGI_FORMAT_ASTC_8X6_TYPELESS;
    case RHIFormat::ASTC_8x8_UNORM:
        return DXGI_FORMAT_ASTC_8X8_UNORM;
    case RHIFormat::ASTC_8x8_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_8X8_UNORM_SRGB;
    case RHIFormat::ASTC_8x8_TYPELESS:
        return DXGI_FORMAT_ASTC_8X8_TYPELESS;
    case RHIFormat::ASTC_10x5_UNORM:
        return DXGI_FORMAT_ASTC_10X5_UNORM;
    case RHIFormat::ASTC_10x5_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_10X5_UNORM_SRGB;
    case RHIFormat::ASTC_10x5_TYPELESS:
        return DXGI_FORMAT_ASTC_10X5_TYPELESS;
    case RHIFormat::ASTC_10x6_UNORM:
        return DXGI_FORMAT_ASTC_10X6_UNORM;
    case RHIFormat::ASTC_10x6_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_10X6_UNORM_SRGB;
    case RHIFormat::ASTC_10x6_TYPELESS:
        return DXGI_FORMAT_ASTC_10X6_TYPELESS;
    case RHIFormat::ASTC_10x8_UNORM:
        return DXGI_FORMAT_ASTC_10X8_UNORM;
    case RHIFormat::ASTC_10x8_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_10X8_UNORM_SRGB;
    case RHIFormat::ASTC_10x8_TYPELESS:
        return DXGI_FORMAT_ASTC_10X8_TYPELESS;
    case RHIFormat::ASTC_10x10_UNORM:
        return DXGI_FORMAT_ASTC_10X10_UNORM;
    case RHIFormat::ASTC_10x10_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_10X10_UNORM_SRGB;
    case RHIFormat::ASTC_10x10_TYPELESS:
        return DXGI_FORMAT_ASTC_10X10_TYPELESS;
    case RHIFormat::ASTC_12x10_UNORM:
        return DXGI_FORMAT_ASTC_12X10_UNORM;
    case RHIFormat::ASTC_12x10_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_12X10_UNORM_SRGB;
    case RHIFormat::ASTC_12x10_TYPELESS:
        return DXGI_FORMAT_ASTC_12X10_TYPELESS;
    case RHIFormat::ASTC_12x12_UNORM:
        return DXGI_FORMAT_ASTC_12X12_UNORM;
    case RHIFormat::ASTC_12x12_UNORM_SRGB:
        return DXGI_FORMAT_ASTC_12X12_UNORM_SRGB;
    case RHIFormat::ASTC_12x12_TYPELESS:
        return DXGI_FORMAT_ASTC_12X12_TYPELESS;
    case RHIFormat::Unknown:
    default:
        assert("Unknow D3D12 format.");
        return DXGI_FORMAT_UNKNOWN;
    }
}

}