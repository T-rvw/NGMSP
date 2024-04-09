#include "D3D12Types.h"

namespace ow
{

D3D12_BLEND_OP ToD3D12(const RHIBlendOperation& rhiType)
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

D3D12_BLEND ToD3D12(const RHIBlendType& rhiType)
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

D3D12_COMMAND_LIST_TYPE ToD3D12(const RHICommandType& rhiType)
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

DXGI_FORMAT ToD3D12(const RHIFormat& rhiType)
{
    switch (rhiType)
    {
    case RHIFormat::Unknown:
        return DXGI_FORMAT_UNKNOWN;
    case RHIFormat::R8G8B8A8Unorm:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    case RHIFormat::R8G8B8A8UnormSrgb:
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    case RHIFormat::R16G16B16A16Float:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case RHIFormat::R32G32Float:
        return DXGI_FORMAT_R32G32_FLOAT;
    case RHIFormat::R32G32B32Float:
        return DXGI_FORMAT_R32G32B32_FLOAT;
    case RHIFormat::R32G32B32A32Float:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case RHIFormat::D32Float:
        return DXGI_FORMAT_D32_FLOAT;
    case RHIFormat::R32Uint:
        return DXGI_FORMAT_R32_UINT;
    case RHIFormat::R16Uint:
        return DXGI_FORMAT_R16_UINT;
    case RHIFormat::D24UnormS8Uint:
        return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case RHIFormat::R11G11B10Float:
        return DXGI_FORMAT_R11G11B10_FLOAT;
    default:
        return DXGI_FORMAT_UNKNOWN;
    }
}

}