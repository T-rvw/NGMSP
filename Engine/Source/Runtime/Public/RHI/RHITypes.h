#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/HAL/Platform.h>

namespace ow
{

enum class GPUVendor
{
    AMD = 0x1002,
    NVIDIA = 0x10DE,
    Intel = 0x8086,
    ARM = 0x13B5,
    ImaginationTechnologies = 0x1010,
    Qualcomm = 0x5143,
    Unknown = -1
};

enum class RHIBackend
{
    Unknown,
    D3D12,
    Vulkan
};

enum class RHIFeature : int64
{
    MeshShaders,
    RayTracing,
    VariableRateShading,
    WorkGraphs
};

struct RHI_API RHIDeviceCreateInfo
{
    RHIDeviceCreateInfo()
    {
        
    }
};

struct RHI_API RHIInstanceCreateInfo
{
    RHIInstanceCreateInfo()
    {
        Backend = RHIBackend::Unknown;
        PreferVender = GPUVendor::Unknown;
        EnableDebugLayer = true;
        EnableGPUValidator = true;
    }

    RHIBackend Backend;
    GPUVendor PreferVender;
    BitFlags<RHIFeature> Features;
    bool EnableDebugLayer;
    bool EnableGPUValidator;
};

}