#pragma once

#include <Core/Base/BitFlags.h>

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

enum class RHIAddressMode
{
    Repeat,
    RepeatMirrored,
    ClampToEdge,
    ClampToBorder,
    MirrorClampToEdge
};

enum class RHIAttachmentLoadOperation
{
    DontCare,
    Clear,
    Load
};

enum class RHIAttachmentStoreOperation
{
    DontCare,
    Store
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
    Max
};

enum class RHIBlendFactor
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
    InvSrc1Alpha
};

enum class RHIBufferUsage
{
    VertexBuffer,
    IndexBuffer,
    UniformBuffer,
    StorageBuffer,
    IndirectBuffer,
    TransferSource,
    TransferTarget,
    TransformFeedbackBuffer,
    TransformFeedbackCounterBuffer
};

enum class RHIColorSpace
{
    SRGB_NONLINEAR,
    DISPLAY_P3_LINEAR,
    DISPLAY_P3_NONLINEAR,
    DCI_P3_LINEAR,
    DCI_P3_NONLINEAR,
    BT709_LINEAR,
    BT709_NONLINEAR,
    BT2020_LINEAR,
    HDR10_ST2084,
    HDR10_HLG,
    DOLBYVISION,
    ADOBERGB_LINEAR,
    ADOBERGB_NONLINEAR
};

enum class RHICommandType
{
    Graphics,
    Compute,
    Copy,
    VideoDecode
};
using RHICommandTypeFlags = BitFlags<RHICommandType>;

enum class RHICullMode
{
    None,
    Front,
    Back
};

enum class RHIDebugMode
{
    Enabled,
    Disabled
};

enum class RHIFeatures
{
    Headless,
    StablePower,
    MeshShaders,
    RayTracing,
    VariableRateShading,
    WorkGraphs
};
using RHIFeatureFlags = BitFlags<RHIFeatures>;

enum class RHIFenceType
{
    Default,
    Shared,
    CrossAdapter
};

enum class RHIFrontFace
{
    Clockwise,
    CounterClockwise
};

enum class RHIPolygonMode
{
    Wireframe,
    Solid
};

enum class RHIFilter
{
    Linear,
    Nearst,
    Cubic
};

enum class RHIFormat
{
    Unknown,

    R8_UINT,
    R8_SINT,
    R8_UNORM,
    R8_SNORM,
    R8_TYPELESS,
    R16_UINT,
    R16_SINT,
    R16_UNORM,
    R16_SNORM,
    R16_FLOAT,
    R16_TYPELESS,
    R32_UINT,
    R32_SINT,
    R32_FLOAT,
    R32_TYPELESS,

    RG8_UINT,
    RG8_SINT,
    RG8_UNORM,
    RG8_SNORM,
    RG8_TYPELESS,
    RG16_UINT,
    RG16_SINT,
    RG16_UNORM,
    RG16_SNORM,
    RG16_FLOAT,
    RG16_TYPELESS,
    RG32_UINT,
    RG32_SINT,
    RG32_FLOAT,
    RG32_TYPELESS,

    B5G6R5_UNORM,
    BGRA4_UNORM,
    B5G5R5A1_UNORM,
    BGRA8_UNORM,
    BGRA8_UNORM_SRGB,
    BGRA8_TYPELESS,
    BGRX8_UNORM,
    BGRX8_UNORM_SRGB,
    BGRX8_TYPELESS,

    RGB32_UINT,
    RGB32_SINT,
    RGB32_FLOAT,
    RGB32_TYPELESS,

    RGBA8_UINT,
    RGBA8_SINT,
    RGBA8_UNORM,
    RGBA8_UNORM_SRGB,
    RGBA8_SNORM,
    RGBA8_TYPELESS,
    RGB10A2_UINT,
    RGB10A2_UNORM,
    RGB10A2_TYPELESS,
    R11G11B10_FLOAT,
    RGBA16_UINT,
    RGBA16_SINT,
    RGBA16_FLOAT,
    RGBA16_UNORM,
    RGBA16_SNORM,
    RGBA16_TYPELESS,
    RGBA32_UINT,
    RGBA32_SINT,
    RGBA32_FLOAT,
    RGBA32_TYPELESS,

    D16_UNORM,
    D24_UNORM_S8_UINT,
    D32_FLOAT,
    D32_FLOAT_S8X24_UINT,

    BC1_UNORM,
    BC1_UNORM_SRGB,
    BC1_TYPELESS,
    BC2_UNORM,
    BC2_UNORM_SRGB,
    BC2_TYPELESS,
    BC3_UNORM,
    BC3_UNORM_SRGB,
    BC3_TYPELESS,
    BC4_UNORM,
    BC4_SNORM,
    BC4_TYPELESS,
    BC5_UNORM,
    BC5_SNORM,
    BC5_TYPELESS,
    BC6H_UFLOAT,
    BC6H_SFLOAT,
    BC6H_TYPELESS,
    BC7_UNORM,
    BC7_UNORM_SRGB,
    BC7_TYPELESS,

    ASTC_4x4_UNORM,
    ASTC_4x4_UNORM_SRGB,
    ASTC_4x4_FLOAT,
    ASTC_4x4_TYPELESS,
    ASTC_5x4_UNORM,
    ASTC_5x4_UNORM_SRGB,
    ASTC_5x4_FLOAT,
    ASTC_5x4_TYPELESS,
    ASTC_5x5_UNORM,
    ASTC_5x5_UNORM_SRGB,
    ASTC_5x5_FLOAT,
    ASTC_5x5_TYPELESS,
    ASTC_6x5_UNORM,
    ASTC_6x5_UNORM_SRGB,
    ASTC_6x5_FLOAT,
    ASTC_6x5_TYPELESS,
    ASTC_6x6_UNORM,
    ASTC_6x6_UNORM_SRGB,
    ASTC_6x6_FLOAT,
    ASTC_6x6_TYPELESS,
    ASTC_8x5_UNORM,
    ASTC_8x5_UNORM_SRGB,
    ASTC_8x5_FLOAT,
    ASTC_8x5_TYPELESS,
    ASTC_8x6_UNORM,
    ASTC_8x6_UNORM_SRGB,
    ASTC_8x6_FLOAT,
    ASTC_8x6_TYPELESS,
    ASTC_8x8_UNORM,
    ASTC_8x8_UNORM_SRGB,
    ASTC_8x8_FLOAT,
    ASTC_8x8_TYPELESS,
    ASTC_10x5_UNORM,
    ASTC_10x5_UNORM_SRGB,
    ASTC_10x5_FLOAT,
    ASTC_10x5_TYPELESS,
    ASTC_10x6_UNORM,
    ASTC_10x6_UNORM_SRGB,
    ASTC_10x6_FLOAT,
    ASTC_10x6_TYPELESS,
    ASTC_10x8_UNORM,
    ASTC_10x8_UNORM_SRGB,
    ASTC_10x8_FLOAT,
    ASTC_10x8_TYPELESS,
    ASTC_10x10_UNORM,
    ASTC_10x10_UNORM_SRGB,
    ASTC_10x10_FLOAT,
    ASTC_10x10_TYPELESS,
    ASTC_12x10_UNORM,
    ASTC_12x10_UNORM_SRGB,
    ASTC_12x10_FLOAT,
    ASTC_12x10_TYPELESS,
    ASTC_12x12_UNORM,
    ASTC_12x12_UNORM_SRGB,
    ASTC_12x12_FLOAT,
    ASTC_12x12_TYPELESS
};

enum class RHIMipmapMode
{
    Linear,
    Nearst
};

enum class RHIPresentMode
{
    VSync,
    Intermediate
};

enum class RHIPrimitiveTopology
{
    PointList,
    LineList,
    LineStrip,
    TriangleList,
    TriangleStrip,
    TriangleFan,
    PatchList
};

enum class RHIShaderLanguage
{
    DXIL,
    GLSL,
    HLSL,
    PSSL,
    SPIRV,
    MSL,
};

enum class RHIShaderStage
{
    Vertex,
    Fragment,
    Compute,
    RayGen,
    AnyHit,
    ClosestHit,
    Miss,
    Intersection,
    Callable,
    Mesh,
    Task
};

enum class RHIShaderType
{
    Compute,
    Fragment,
    Mesh,
    Task,
    Vertex,
};

enum class RHITextureType
{
    Texture1D,
    Texture2D,
    Texture3D,
    Texture1DArray,
    Texture2DArray,
    TextureCube,
    TextureCubeArray
};

enum class RHITextureUsage
{
    SampledTexture,
    StorageTexture,
    TransferSource,
    TransferTarget
};

enum class RHIValidationMode
{
    CPUOnly,
    GPU,
    Disabled
};

enum class RHIVertexInputRate
{
    Instance,
    Vertex
};

}