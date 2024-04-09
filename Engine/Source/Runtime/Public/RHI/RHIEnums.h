#pragma once

namespace ow
{

enum class GPUVendor
{
    AMD,
    ARM,
    ImaginationTechnologies,
    Intel,
    NVIDIA,
    Qualcomm
};

enum class GPUAdapterType
{
    Discrete,
    Integrated,
    Virtual,
    CPU
};

enum class RHIBackend
{
    D3D12,
    Vulkan
};

enum class RHIBlendOperation
{
    Add,
    Subtract,
    RevSubtract,
    Min,
    Max,
};

enum class RHIBlendType
{
    Zero,
    One,
    SrcColor,
    InvSrcColor,
    SrcAlpha,
    InvSrcAlpha,
    DestAlpha,
    InvDestAlpha,
    DestColor,
    InvDestColor,
    SrcAlphaSat,
    BlendFactor,
    InvBlendFactor,
    Src1Color,
    InvSrc1Color,
    Src1Alpha,
    InvSrc1Alpha,
};

enum class RHICommandType
{
    Graphics,
    Compute,
    Copy,
    VideoDecode
};

enum class RHICullMode
{
    None,
    Front,
    Back
};

enum class RHIDebugMode
{
    Normal,
    Disabled
};

enum class RHIFillMode
{
    Wireframe,
    Solid
};

enum class RHIFormat
{
    Unknown,
    R8G8B8A8Unorm,
    R8G8B8A8UnormSrgb,
    R11G11B10Float,
    R16G16B16A16Float,
    R32G32Float,
    R32G32B32Float,
    R32G32B32A32Float,
    D32Float,
    R32Uint,
    R16Uint,
    D24UnormS8Uint
};

enum class RHIPresentMode
{
    VSync,
    Intermediate
};

enum class RHIPrimitiveType
{
    PointList,
    LineList,
    LineStrip,
    TriangleList,
    TriangleStrip
};

enum class RHIShaderType
{
    Compute,
    Fragment,
    Vertex
};

enum class RHIValidationMode
{
    CPUOnly,
    GPU,
    Disabled
};

}