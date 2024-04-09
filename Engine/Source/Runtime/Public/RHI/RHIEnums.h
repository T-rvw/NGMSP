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

enum class RHICommandQueueType
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