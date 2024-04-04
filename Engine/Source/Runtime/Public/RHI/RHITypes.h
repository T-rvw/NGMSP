#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

enum class GPUVendor
{
    Unknown,
    AMD,
    ARM,
    ImaginationTechnologies,
    Intel,
    NVIDIA,
    Qualcomm
};

template<GPUVendor T>
constexpr uint32 GetGPUVendorID()
{
    if constexpr (GPUVendor::Unknown == T)
    {
        return -1;
    }
    else if constexpr (GPUVendor::AMD == T)
    {
        return 0x1002;
    }
    else if constexpr (GPUVendor::ARM == T)
    {
        return 0x13B5;
    }
    else if constexpr (GPUVendor::ImaginationTechnologies == T)
    {
        return 0x1010;
    }
    else if constexpr (GPUVendor::Intel == T)
    {
        return 0x8086;
    }
    else if constexpr (GPUVendor::NVIDIA == T)
    {
        return 0x10DE;
    }
    else if constexpr (GPUVendor::Qualcomm == T)
    {
        return 0x5143;
    }
}

static GPUVendor GetGPUVendor(uint32 vendorID)
{
    if (GetGPUVendorID<GPUVendor::AMD>() == vendorID)
    {
        return GPUVendor::AMD;
    }
    else if (GetGPUVendorID<GPUVendor::ARM>() == vendorID)
    {
        return GPUVendor::ARM;
    }
    else if (GetGPUVendorID<GPUVendor::ImaginationTechnologies>() == vendorID)
    {
        return GPUVendor::ImaginationTechnologies;
    }
    else if (GetGPUVendorID<GPUVendor::Intel>() == vendorID)
    {
        return GPUVendor::Intel;
    }
    else if (GetGPUVendorID<GPUVendor::NVIDIA>() == vendorID)
    {
        return GPUVendor::NVIDIA;
    }
    else if (GetGPUVendorID<GPUVendor::Qualcomm>() == vendorID)
    {
        return GPUVendor::Qualcomm;
    }
    else
    {
        return GPUVendor::Unknown;
    }
}

enum class GPUAdapterType
{
    Unknown,
    Discrete,
    Integrated,
    Virtual,
    CPU
};

enum class RHIBackend
{
    Unknown,
    D3D12,
    Vulkan
};

struct RHI_API RHIFeatures
{
    bool Barycentrics : 1;
    bool ShaderFloat16 : 1;
    bool Headless : 1;
    bool MeshShaders : 1;
    bool RayTracing : 1;
    bool VariableRateShading : 1;
    bool WorkGraphs : 1;
};

struct RHIAdapterInfo
{
    RHIAdapterInfo()
    {
        Type = GPUAdapterType::Unknown;
        Vendor = GPUVendor::Unknown;
        VendorID = 0;
        DeviceID = 0;
        VideoMemorySize = 0;
        SystemMemorySize = 0;
        SharedMemorySize = 0;
        Name = "Unknown";
    }

    GPUAdapterType Type;
    GPUVendor Vendor;
    uint32 VendorID;
    uint32 DeviceID;
    uint64 VideoMemorySize;
    uint64 SystemMemorySize;
    uint64 SharedMemorySize;
    std::string Name;
};

struct RHI_API RHIDeviceCreateInfo
{
    RHIDeviceCreateInfo()
    {
    }

    RHIFeatures Features;
};

enum class DebugMode
{
    Normal,
    Disabled
};

enum class ValidationMode
{
    CPUOnly,
    GPU,
    Disabled
};

struct RHI_API RHIInstanceCreateInfo
{
    RHIInstanceCreateInfo()
    {
        Backend = RHIBackend::Unknown;
        Debug = DebugMode::Disabled;
        Validation = ValidationMode::Disabled;
    }

    RHIBackend Backend;
    DebugMode Debug;
    ValidationMode Validation;
};

}