#pragma once

#include <Core/Base/NameOf.h>
#include <Core/HAL/APIDefines.h>
#include <Core/HAL/BasicTypes.h>
#include <Core/String/String.h>
#include <RHI/RHIEnums.h>
#include <RHI/RHIFoward.h>

namespace ow
{

template<GPUVendor T>
constexpr uint32 GetGPUVendorID()
{
    if constexpr (GPUVendor::AMD == T)
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
        return GPUVendor::AMD;
    }
}

struct RHIAdapterInfo
{
    GPUAdapterType Type = GPUAdapterType::CPU;
    GPUVendor Vendor = GPUVendor::AMD;
    uint32 VendorID = 0;
    uint32 DeviceID = 0;
    uint64 VideoMemorySize = 0;
    uint64 SystemMemorySize = 0;
    String Name = "Unknown";

    void Dump() const
    {
        printf("[RHIAdapterInfo] Name = %s\n", Name.c_str());
        printf("\tVendor = %s\n", EnumName(Vendor).data());
        printf("\tVendorID = %u\n", VendorID);
        printf("\tDeviceID = %u\n", DeviceID);
        printf("\tVideoMemorySize = %llu MB\n", VideoMemorySize >> 20);
        printf("\tSystemMemorySize = %llu MB\n", SystemMemorySize >> 20);
    }
};

struct RHIOutputInfo
{
    uint32 Width;
    uint32 Height;
    RHIColorSpace ColorSpace;
    uint32 BitsPerColor;
    float MinLuminance;
    float MaxLuminance;
    float MaxFullFrameLuminance;
    String Name = "Unknown";

    void Dump() const
    {
        printf("[RHIOutputInfo] Name = %s\n", Name.c_str());
        printf("\tWidth = %u, Height = %u\n", Width, Height);
        printf("\tColorSpace = %s\n", EnumName(ColorSpace).data());
        printf("\tBitsPerColor = %u\n", BitsPerColor);
        printf("\tMinLuminance = %f\n", MinLuminance);
        printf("\tMaxLuminance = %f\n", MaxLuminance);
        printf("\tMaxFullFrameLuminance = %f\n", MaxFullFrameLuminance);
    }
};

struct RHIBarrierCreateInfo
{
};

struct RHIBufferCreateInfo
{
    uint32 SizeInBytes;
    uint32 Stride;
    uint32 Count;
    RHIBufferUsage Usage;
};

struct RHICommandListCreateInfo
{
    uint32 BufferCount = 1;
};

struct RHICommandPoolCreateInfo
{
    RHICommandType Type = RHICommandType::Graphics;
};

struct RHICommandQueueCreateInfo
{
    RHICommandType Type = RHICommandType::Graphics;
    uint32 FamilyIndex = 0;
    uint32 QueueIndex = 0;
    float Priority = 1.0f;
    bool IsDedicated = false;
};

struct RHIDeviceCreateInfo
{
    RHIDebugMode Debug = RHIDebugMode::Disabled;
    RHIValidationMode Validation = RHIValidationMode::Disabled;
    RHIFeatureFlags Features;
    RHICommandTypeFlags CommandQueueTypes;
};

struct RHIFenceCreateInfo
{
    RHIFenceType FenceType = RHIFenceType::Default;
    uint64 InitialValue = 0;
};

struct RHIInstanceCreateInfo
{
    RHIFeatureFlags Features;
    RHIDebugMode Debug = RHIDebugMode::Disabled;
    RHIValidationMode Validation = RHIValidationMode::Disabled;
};

struct RHIPipelineLayoutCreateInfo
{
};

struct RHIComputePipelineStateCreateInfo
{
};

struct RHIGraphicsPipelineStateCreateInfo
{
    IRHISwapChain* SwapChain = nullptr;
    RefCountPtr<IRHIShader> VertexShaderBlob;
    RefCountPtr<IRHIShader> FragmentShaderBlob;

    // Input Assembly
    RHIPrimitiveTopology Topology = RHIPrimitiveTopology::TriangleList;

    // Rasterization
    RHIPolygonMode PolygonMode = RHIPolygonMode::Solid;
    RHICullMode CullMode = RHICullMode::Back;
    RHIFrontFace FrontFace = RHIFrontFace::Clockwise;
};

struct RHIRaytracingPipelineStateCreateInfo
{

};

struct RHISamplerCreateInfo
{

};

struct RHISemaphoreCreateInfo
{

};

struct RHIShaderCreateInfo
{
};

struct RHISwapChainCreateInfo
{
    void* NativeInstanceHandle = nullptr;
    void* NativeWindowHandle = nullptr;
    RHIFormat Format = RHIFormat::RGBA8_UNORM;
    RHIColorSpace ColorSpace = RHIColorSpace::SRGB_NONLINEAR;
    uint32 BackBufferWidth = 1;
    uint32 BackBufferHeight = 1;
    uint32 BackBufferCount = 2;
    RHIPresentMode PresentMode = RHIPresentMode::VSync;
};

struct RHITextureCreateInfo
{

};

}