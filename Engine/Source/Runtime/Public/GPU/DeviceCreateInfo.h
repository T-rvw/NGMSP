#pragma once

#include <Core/Base/BitFlags.h>
#include <Core/HAL/Platform.h>

namespace ow::gpu
{

enum class Vendor
{
    AMD = 0x1002,
    NVIDIA = 0x10DE,
    Intel = 0x8086,
    ARM = 0x13B5,
    ImaginationTechnologies = 0x1010,
    Qualcomm = 0x5143,
    Unknown = -1
};

enum class Feature : int64
{
    MeshShader,
    RayTracing,
    VariableRateShading,
    WorkGraphs
};

struct ENGINE_API DeviceCreateInfo
{
    DeviceCreateInfo()
    {
        PreferVender = Vendor::Unknown;
    }

    Vendor PreferVender;
    BitFlags<Feature> Features;
};

}